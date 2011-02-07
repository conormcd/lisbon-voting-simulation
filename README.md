INTRODUCTION
------------

This is a program which brute-forces all permutations of voting in the Council
of the European Union to show the number of times a country gets its way both
before and after the Treaty of Lisbon comes into effect.

HOW TO BUILD AND RUN THE PROGRAM
--------------------------------

The program was developed on a Mac and while every effort was made to only use
standard, widely available library functions you may have trouble building or
running it on another platform. Patches to make the program more portable would
be much appreciated.

On any Mac or UNIX-like operating system with gcc and make installed, building
the program should be as simple as typing "make" at a command prompt in the
directory where the source and Makefile are.

GLOSSARY / EXPLANATION OF THE CONCEPTS
--------------------------------------

<dl>
	<dt>Nice 50%</dt>
	<dd>A voting method set out in the Nice Treaty. For a decision to pass it
		must have a majority of the countries in favour, at least 74% of the
		weighted votes in favour and 62% of the population in favour.
	</dd>
	<dt>Nice 67%</dt>
	<dd>A voting method set out in the Nice Treaty. For a decision to pass it
		must have a two-thirds majority of countries in favour, 74% of the
		weighted votes in favour and 62% of the population in favour.
	</dd>
	<dt>TEU 16 (4)</dt>
	<dd>A voting method described in the Lisbon Treaty. For a decision to pass
		it must have 55% of countries in favour and 65% of the population in
		favour. A decision may be blocked by any four countries.
	</dd>
	<dt>TFEU 238 (1)</dt>
	<dd>A voting method described in the Lisbon Treaty. For a decision to pass,
		a simple majority of countries is required.
	</dd>
	<dt>TFEU 238 (2)</dt>
	<dd>A voting method described in the Lisbon Treaty. For a decision to pass,
		72% of countries and 65% of the population must be in favour.
	</dd>
	<dt>influence</dt>
	<dd>A participant in a vote has "influence" if the outcome of a vote would
		change if that participant changed their vote.
	</dd>
	<dt>win</dt>
	<dd>Where the outcome of a vote matches the vote that a participant
		made.
	</dd>
</dl>

Examples:

<table>
	<tr><th></th><th>Alice</th><th>Bob</th><th>Charlie</th></tr>
	<tr><th>Vote 1</th><td>Yes</td><td>Yes</td><td>No</td></tr>
	<tr><th>Vote 2</th><td>No</td><td>Yes</td><td>No</td></tr>
	<tr><th>Vote 3</th><td>Yes</td><td>Yes</td><td>Yes</td></tr>
</table>

In vote 1, Alice and Bob both win and both have influence.
In vote 2, Alice and Charlie both win and both have influence.
In vote 3, Alice, Bob and Charlie all win but none of them have influence.
