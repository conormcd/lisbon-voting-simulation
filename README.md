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

* In vote 1, Alice and Bob both win and both have influence.
* In vote 2, Alice and Charlie both win and both have influence.
* In vote 3, Alice, Bob and Charlie all win but none of them have influence.

RESULTS
-------

Here is the output the program produces:

<pre>
Number of countries:           27
Number of voting permutations: 134217728
Number of voting methods:      5

"Wins" by country and voting method:

                Nice 50%  Nice 67%  TEU 16 (4)  TFEU 238 (1)  TFEU 238 (2)  
Austria         67935350  67867657    67111454      77509464      67634816  
Belgium         68091934  67965305    67111454      77509464      67640436  
Bulgaria        67935350  67867657    67111454      77509464      67633544  
Cyprus          67444384  67565761    67111454      77509464      67620020  
Czech Republic  68091934  67965305    67111454      77509464      67638332  
Denmark         67692480  67719853    67111454      77509464      67628780  
Estonia         67444384  67565761    67111454      77509464      67620976  
Finland         67692480  67719853    67111454      77509464      67628658  
France          69177624  68669973    67111464      77509464      67768654  
Germany         69177624  68669973    67111472      77509464      67839364  
Greece          68091934  67965305    67111454      77509464      67640436  
Hungary         68091934  67965305    67111454      77509464      67638332  
Ireland         67692480  67719853    67111454      77509464      67626524  
Italy           69177624  68669973    67111464      77509464      67755348  
Latvia          67444384  67565761    67111454      77509464      67622890  
Lithuania       67692480  67719853    67111454      77509464      67624900  
Luxembourg      67444384  67565761    67111454      77509464      67619358  
Malta           67360308  67509981    67111454      77509464      67619216  
Netherlands     68170648  68013311    67111454      77509464      67656000  
Poland          69083206  68592905    67111460      77509464      67703908  
Portugal        68091934  67965305    67111454      77509464      67640436  
Romania         68247372  68065305    67111454      77509464      67664486  
Slovakia        67692480  67719853    67111454      77509464      67628780  
Slovenia        67444384  67565761    67111454      77509464      67622350  
Spain           69083206  68592905    67111460      77509464      67712100  
Sweden          67935350  67867657    67111454      77509464      67636194  
UK              69177624  68669973    67111464      77509464      67758640  

"Influences" by country and voting method:

                Nice 50%  Nice 67%  TEU 16 (4)  TFEU 238 (1)  TFEU 238 (2)  
Austria          1652972   1517586        5180      20801200       1051904  
Belgium          1966140   1712882        5180      20801200       1063144  
Bulgaria         1652972   1517586        5180      20801200       1049360  
Cyprus            671040    913794        5180      20801200       1022312  
Czech Republic   1966140   1712882        5180      20801200       1058936  
Denmark          1167232   1221978        5180      20801200       1039832  
Estonia           671040    913794        5180      20801200       1024224  
Finland          1167232   1221978        5180      20801200       1039588  
France           4137520   3122218        5200      20801200       1319580  
Germany          4137520   3122218        5216      20801200       1461000  
Greece           1966140   1712882        5180      20801200       1063144  
Hungary          1966140   1712882        5180      20801200       1058936  
Ireland          1167232   1221978        5180      20801200       1035320  
Italy            4137520   3122218        5200      20801200       1292968  
Latvia            671040    913794        5180      20801200       1028052  
Lithuania        1167232   1221978        5180      20801200       1032072  
Luxembourg        671040    913794        5180      20801200       1020988  
Malta             502888    802234        5180      20801200       1020704  
Netherlands      2123568   1808894        5180      20801200       1094272  
Poland           3948684   2968082        5192      20801200       1190088  
Portugal         1966140   1712882        5180      20801200       1063144  
Romania          2277016   1912882        5180      20801200       1111244  
Slovakia         1167232   1221978        5180      20801200       1039832  
Slovenia          671040    913794        5180      20801200       1026972  
Spain            3948684   2968082        5192      20801200       1206472  
Sweden           1652972   1517586        5180      20801200       1054660  
UK               4137520   3122218        5200      20801200       1299552  
</pre>
