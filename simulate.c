/*
	Copyright (c) 2008, 2009, 2011
	Conor McDermottroe.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:
	1. Redistributions of source code must retain the above copyright
	   notice, this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.
	3. Neither the name of the author nor the names of any contributors to
	   the software may be used to endorse or promote products derived from
	   this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
	TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
	OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
	OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
	NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	PERCENT(a, b)	(((double)(a) / (double)(b)) * 100)

typedef struct {
	char*		name;			// Name of the country
	uint8_t		nice_weight;	// The QMV weighting under Nice Treaty rules
	uint32_t	population;		// The population, in thousands (Wikipedia)
} country_t;

typedef struct {
	uint8_t		countries;			// The number of countries seen
	uint8_t		countries_for;		// The number of countries voting yes.
	uint8_t		countries_against;	// The number of countries voting no.
	double		countries_for_pc;	// The "yes" votes as a percentage
	uint32_t	population;			// The total population of the countries seen.
	uint32_t	population_for;		// The total population of countries voting yes.
	uint32_t	population_against;	// The total population of countries voting no.
	double		population_for_pc;	// The population of the countries voting yes as a percentage of total population.
	uint16_t	nice_votes;			// The number of Nice weighted votes cast.
	uint16_t	nice_votes_for;		// The number of Nice weighted votes which were yes.
	uint16_t	nice_votes_against;	// The number of Nice weighted votes which were no.
	double		nice_votes_for_pc;	// The "yes" weighted Nice votes as a percentage of the total.
} analysis_t;

// The voting method callback signature.
typedef bool voting_method(analysis_t* analysis);

typedef struct {
	voting_method*	function;	// A pointer to the function which evaluates the votes and calculates the result
	char*			name;		// The name of the voting method.
} method_t;

// All the member states of the EU.
country_t countries[] = {
	{ "Austria",		10,	8300 },
	{ "Belgium",		12,	11000 },
	{ "Bulgaria",		10,	7700 },
	{ "Cyprus",			4,	770 },
	{ "Czech Republic", 12,	10000 },
	{ "Denmark",		7,	5400 },
	{ "Estonia",		4,	1300 },
	{ "Finland",		7,	5300 },
	{ "France",			29,	63000 },
	{ "Germany",		29,	82000 },
	{ "Greece",			12,	11000 },
	{ "Hungary",		12,	10000 },
	{ "Ireland",		7,	4200 },
	{ "Italy",			29,	59000 },
	{ "Latvia",			4,	2300 },
	{ "Lithuania",		7,	3400 },
	{ "Luxembourg",		4,	460 },
	{ "Malta",			3,	400 },
	{ "Netherlands",	13,	18000 },
	{ "Poland",			27,	38000 },
	{ "Portugal",		12,	11000 },
	{ "Romania",		14,	22000 },
	{ "Slovakia",		7,	5400 },
	{ "Slovenia",		4,	2000 },
	{ "Spain",			27,	44000 },
	{ "Sweden",			10,	9000 },
	{ "UK",				29,	60000 },
	{ NULL, 0, 0 },
};

// To pass:	Majority of countries
//			AND
//			74% of the weighted votes
//			AND
//			62% of the population
bool nice_50(analysis_t* analysis) {
	return	analysis->countries_for > analysis->countries_against &&
			analysis->nice_votes_for_pc >= 74.0 &&
			analysis->population_for >= 62.0;
}

// To pass:	2/3s of countries
//			AND
//			74% of the weighted votes
//			AND
//			62% of the population
bool nice_67(analysis_t* analysis) {
	return	analysis->countries_for_pc >= 66.666 &&
			analysis->nice_votes_for_pc >= 74.0 &&
			analysis->population_for >= 62.0;
}

// To pass:		55% of countries
//				AND
//				65% of population
// To block:	4 countries against
bool teu_16_4(analysis_t* analysis) {
	if (analysis->countries_against >= 4) {
		return false;
	}
	return	analysis->countries_for_pc >= 55.0 &&
			analysis->population_for_pc >= 65.0;
}

// Simple majority
bool tfeu_238_1(analysis_t* analysis) {
	return analysis->countries_for > analysis->countries_against;
}

// To pass:		72% of countries
//				65% of population
bool tfeu_238_2(analysis_t* analysis) {
	return	analysis->countries_for_pc >= 72.0 &&
			analysis->population_for_pc >= 65.0;
}

// All the voting methods
method_t voting_methods[] = {
	{ &nice_50, "Nice 50%" },
	{ &nice_67, "Nice 67%" },
	{ &teu_16_4, "TEU 16 (4)" },
	{ &tfeu_238_1, "TFEU 238 (1)" },
	{ &tfeu_238_2, "TFEU 238 (2)" },
	{ 0, 0 },
};

// Fill out an analysis_t based on a single round of voting.
void analyse(uint32_t vote, analysis_t* analysis) {
	// Reset the analysis
	bzero(analysis, sizeof(analysis_t));

	// Calculate the stats
	for (uint8_t bit = 0; countries[bit].name != NULL; bit++) {
		analysis->countries++;
		analysis->population += countries[bit].population;
		analysis->nice_votes += countries[bit].nice_weight;
		if (vote & (1 << bit)) {
			// The country voted for the proposal
			analysis->countries_for++;
			analysis->population_for += countries[bit].population;
			analysis->nice_votes_for += countries[bit].nice_weight;
		}
	}
	analysis->countries_against = analysis->countries - analysis->countries_for;
	analysis->population_against = analysis->population - analysis->population_for;
	analysis->nice_votes_against = analysis->nice_votes - analysis->nice_votes_for;

	// Now calculate the percentages
	analysis->countries_for_pc = PERCENT(analysis->countries_for, analysis->countries);
	analysis->population_for_pc = PERCENT(analysis->population_for, analysis->population);
	analysis->nice_votes_for_pc = PERCENT(analysis->nice_votes_for, analysis->nice_votes);
}

int main() {
	// Find out the number of countries we have
	uint8_t num_countries = 0;
	while (countries[num_countries].name != NULL) {
		num_countries++;
	}

	// Find the maximum number of vote permutations
	uint32_t max_vote_permutations = 1 << num_countries;

	// And how many voting methods
	uint8_t num_methods = 0;
	while (voting_methods[num_methods].name != NULL) {
		num_methods++;
	}

	// Make space for the results
	uint8_t* results = calloc(max_vote_permutations, sizeof(uint8_t));
	uint32_t* wins = calloc(max_vote_permutations, sizeof(uint32_t));
	uint32_t* influences = calloc(max_vote_permutations, sizeof(uint32_t));

	// Work through all of the vote permutations analysing each one
	analysis_t analysis;
	for (uint32_t vote_permutation = 0; vote_permutation < max_vote_permutations; vote_permutation++) {
		// Analyse the vote
		analyse(vote_permutation, &analysis);
		for (uint8_t method = 0; method < num_methods; method++) {
			bool vote_result = voting_methods[method].function(&analysis);

			// Record the result
			if (vote_result) {
				results[vote_permutation] |= (1 << method);
			}

			// Count the wins per country
			for (uint8_t country = 0; country < num_countries; country++) {
				// Find out which way the current country voted
				bool country_vote = false;
				if (vote_permutation & (1 << country)) {
					country_vote = true;
				}

				if (vote_result == country_vote) {
					wins[(country * num_methods) + method]++;
				}
			}
		}
	}

	// Now work out the influence scores
	for (uint32_t vote_permutation = 0; vote_permutation < max_vote_permutations; vote_permutation++) {
		for (uint8_t country = 0; country < num_countries; country++) {
			for (uint8_t method = 0; method < num_methods; method++) {
				if (vote_permutation > (vote_permutation ^ (1 << country))) { // Symmetrical, only bother calculating one.
					bool this_result = false;
					if (results[vote_permutation] & (1 << method)) {
						this_result = true;
					}
					bool country_vote_changed_result = false;
					if (results[vote_permutation ^ (1 << country)] & (1 << method)) {
						country_vote_changed_result = true;
					}

					if (this_result != country_vote_changed_result) {
						influences[(country * num_methods) + method] += 2;
					}
				}
			}
		}
	}

	// We're done with the results
	free(results);

	// Produce the results
	uint8_t output_rows = num_countries + 1;
	uint8_t output_columns = num_methods + 1;
	char** output_wins = calloc(output_rows * output_columns, sizeof(char*));
	char** output_influences = calloc(output_rows * output_columns, sizeof(char*));
	for (uint8_t i = 0; i < output_rows * output_columns; i++) {
		output_wins[i] = "";
		output_influences[i] = "";
	}

	// Put in the row headings and column headings
	for (uint8_t country = 0; country < num_countries; country++) {
		output_wins[(country + 1) * output_columns] = countries[country].name;
		output_influences[(country + 1) * output_columns] = countries[country].name;
	}
	for (uint8_t method = 0; method < num_methods; method++) {
		output_wins[method + 1] = voting_methods[method].name;
		output_influences[method + 1] = voting_methods[method].name;
	}

	// Now fill in the data
	for (uint8_t country = 0; country < num_countries; country++) {
		for (uint8_t method = 0; method < num_methods; method++) {
			uint8_t row = country + 1;
			uint8_t col = method + 1;

			char buffer[256];

			// Wins
			memset(buffer, 0, 256);
			snprintf(buffer, 256, "%d", wins[(country * num_methods) + method]);
			output_wins[(row * output_columns) + col] = strdup(buffer);

			// Influences
			memset(buffer, 0, 256);
			snprintf(buffer, 256, "%d", influences[(country * num_methods) + method]);
			output_influences[(row * output_columns) + col] = strdup(buffer);
		}
	}

	// Now we're done with the calculated values
	free(wins);
	free(influences);

	// Find the widths of all the columns
	uint8_t* column_widths = calloc(output_columns, sizeof(uint8_t));
	for (uint8_t i = 0; i < output_rows; i++) {
		for (uint8_t j = 0; j < output_columns; j++) {
			uint8_t col_width = strlen(output_wins[(i * output_columns) + j]);
			if (col_width > column_widths[j]) {
				column_widths[j] = col_width;
			}
			col_width = strlen(output_influences[(i * output_columns) + j]);
			if (col_width > column_widths[j]) {
				column_widths[j] = col_width;
			}
		}
	}

	// Print the results
	printf("Number of countries:           %d\n", num_countries);
	printf("Number of voting permutations: %d\n", max_vote_permutations);
	printf("Number of voting methods:      %d\n", num_methods);
	printf("\n");
	printf("\"Wins\" by country and voting method:\n");
	printf("\n");
	for (uint8_t i = 0; i < output_rows; i++) {
		for (uint8_t j = 0; j < output_columns; j++) {
			char format_string[8];
			memset(format_string, 0, 8);
			if (j == 0) {
				snprintf(format_string, 8, "%%-%ds  ", column_widths[j]);
			} else {
				snprintf(format_string, 8, "%%%ds  ", column_widths[j]);
			}
			printf(format_string, output_wins[(i * output_columns) + j]);
			if (i > 0 && j > 0) {
				free(output_wins[(i * output_columns) + j]);
			}
		}
		printf("\n");
	}
	printf("\n");
	printf("\"Influences\" by country and voting method:\n");
	printf("\n");
	for (uint8_t i = 0; i < output_rows; i++) {
		for (uint8_t j = 0; j < output_columns; j++) {
			char format_string[8];
			memset(format_string, 0, 8);
			if (j == 0) {
				snprintf(format_string, 8, "%%-%ds  ", column_widths[j]);
			} else {
				snprintf(format_string, 8, "%%%ds  ", column_widths[j]);
			}
			printf(format_string, output_influences[(i * output_columns) + j]);
			if (i > 0 && j > 0) {
				free(output_influences[(i * output_columns) + j]);
			}
		}
		printf("\n");
	}

	// Clean up
	free(output_wins);
	free(output_influences);

	return 0;
}
