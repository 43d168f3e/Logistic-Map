# Logistic-Map
Chaotic Logistic Map [LM]: Investigation of the [1] spacing; and [2] vertical width of the infinity of horizontal 'voids,' or bands, that occur in the LM.
# Chaotic Logistic Map

 PURPOSE: Investigation of the 

    [1] spacing; and 
    [2] vertical width 
    
of the infinity of horizontal 'voids,' or <font color="#bf0041">bands</font> [e.g., re figures below] that occur in certain regions of the Logistic Map (LM);
In this note the points of the LM are labeled with coordinates ( x, R ).
The ‘normalized population’ x, 0 &lt;= x &lt;= 1, is the
horizontal coordinate (abscissa). The ‘effective birth rate’ R,
2.9 &lt;= R &lt;= 4, is the vertical coordinate (ordinate). 

    [3] For each R, assign musical notes to the { x }; play the resulting 'music.'

For fixed R, the points of the LM  ( x<sub>0</sub>, R ),  ( x<sub>1</sub>, R ),  ( x<sub>2</sub>, R ), ... ,  that lie in a single row may be computed iteratively using the rule

x<sub>n+1</sub> = R * x<sub>n</sub> * (1 - x<sub>n</sub>) = f<sub>R</sub>( x<sub>n</sub> )

Representative points for the LM are then calculated by picking values for R  that lie in the range 2.9 &lt;= R &lt;= 4 and computing iteratively using this rule, row after row.

For our purposes a "<font color="#bf0041">band</font>” is simply a region that is traversed
from below [i.e., from smaller to larger values of R] by a finite
number of curves, x = x(R), that express the periodicity [as opposed
to the chaos] at the lower boundary of the region. 

<p style="margin-bottom:20px;">
	<img src="figure-2.png" name="Image1" align="top" />
</p>

<p style="margin-bottom:20px;">
abscissa: 'normalized population x:' 0 &lt;= x &lt;= 1 ) <br/>
ordinate: ‘effective birth rate R:' 3.63 &lt; R &lt;= 4
</p>

<p style="margin-top:20px;margin-bottom:20px;">
	<img src="figure-3.png" name="Image2" align="top" />
</p>

<p style="margin-bottom:20px;">
abscissa: 'normalized population x:' 0.2 &lt; x &lt; 0.9 ) <br/>
ordinate: ‘effective birth rate R:' 3.71 &lt; R &lt; 3.77
</p>


<font size="4" style="font-size: 16pt"><b>Usage: (after downloading and building [e.g., use qt creator]) </b></font>

<ol>
	<li><font size="4" style="font-size: 14pt"><span style="font-weight: normal">To
	execute, click on</span><b> <font color="#bf0041">Logistic_Map</font>,
	</b><span style="font-weight: normal">or </span><span style="font-weight: normal">type
	and enter</span><b> <font color="#bf0041">Logistic_Map
	previous_session.json</font> </b><span style="font-weight: normal">from
	a terminal window;</span><b>  </b><span style="font-weight: normal">here</span><b>
	</b><span style="font-weight: normal">&quot;previous_session.json&quot;
	represents any file that you created earlier.</span></font>
	<li><font size="4" style="font-size: 14pt"><b><font color="#ce181e">zoom
	in:</font> </b><span style="font-weight: normal">right-click and
	hold button down, 'drag' a rectangular boundary, then release the
	right-click; i.e., right-drag a ‘selection rectangle’ within the
	figure to zoom into the rectangle, or, if the SHIFT key is pressed when releasing the mouse button, 
	play 'musically' the selected rectangle.</span></font>
	<li><font size="4" style="font-size: 16pt"><b><font color="#ce181e"><font size="4" style="font-size: 14pt">translate
	origin to a point:</font></font> </b><font size="4" style="font-size: 14pt"><span style="font-weight: normal">left-click
	on the point for the new origin.</span></font></font>
	<li><font size="4" style="font-size: 16pt"><b><font color="#bf0041"><font size="4" style="font-size: 14pt">record
	the (x, y) == (x, R) coordinates of a particular</font></font><font color="#bf0041">
	</font><font color="#bf0041"><font size="4" style="font-size: 14pt">point-of-interest
	[P.O.I]:</font></font></b></font>
</ol>
<ol type="a">
	<li><p align="center"> <font color="#158466"><font size="4" style="font-size: 14pt">control-left-click</font></font><font size="4" style="font-size: 14pt">
	on the point; you may enter a label for this point</font>
	<li><p align="center"><font size="4" style="font-size: 14pt"><font color="#158466">control-shift-left-click</font>;
	            no user-defined label for this P.O.I</font>
</ol>

<ul>
	<li>A <font color="#bf0041"><font size="4" style="font-size: 14pt">history</font></font>
	of is created for each session. This history includes: left, right,
	bottom and top coordinate boundaries for each rectangle, and any
	P.O.I. that you recorded. 
	<li>A <font color="#bf0041">visual summary</font> of this history
	appears as a &quot;dialog window&quot; [DW] adjacent to the main
	window.
	<li>Click on the <font color="#ce181e">left-border item numbers</font>
	of the DW to inspect the boundary coordinates.
	<li>Click on the <font color="#ce181e">interior of this window</font>
	of the DW to go back to a previous region.
	<li>A <font color="#ce181e">png image of any particular image may
	be saved by using the menu-File-&gt;Save</font> option;
	<li>Alternately, if the <font color="#ce181e">Auto-Save checkbox
	is selected</font>, a png file is created for each figure.
	<li>The <font color="#ce181e"><font size="3" style="font-size: 13pt">number
	of points calculated per pixel row</font></font> may be increased or
	decreased, in a hopefully obvious mannner.
	<li>You may also choose the <font color="#ce181e"><font size="4" style="font-size: 14pt">number
	of threads</font></font> to commit to a computation.
	<li>You may <font color="#ce181e"><font size="4" style="font-size: 15pt"><b>create
	&quot;music</b></font></font>al tones&quot; as the LM points are
	computed, also in a hopefully obvious manner.
</ul>

<font size="4" style="font-size: 16pt"><b>Appendix: </b></font>To generate figure 1: 


<div id="mypng1">
	<img src="figure-1.png" name="Image1" align="left" />
</div>

Values of R are selected uniformly from the range 2.9 to 4 at
evenly spaced ordinare values. For each of these R values a pseudo-random
initial value x<sub>0</sub>,  0 &lt; x<sub>0</sub> &lt; 1 is chosen for x. Then a sequence of
abscissa x<sub>1</sub> = f<sub>R</sub>(x<sub>0</sub>), x<sub>2</sub> = f<sub>R</sub>(x<sub>1</sub>), x<sub>3</sub> = f<sub>R</sub>(x<sub>2</sub>), … is calculated. This
sequence is called an orbit. Then some of the points, say, the first
one or two thousand, are discarded, with the hope that the remaining
(x, R) are near convergence to their respective attractor [if any];
the remaining ( x<sub>2000</sub>, R ), ( x<sub>2001</sub>, R ), …, ( x<sub>last</sub>, R ), …
are plotted. 


<font color="#ce181e"><font size="4" style="font-size: 16pt"><b>Ranges: for each rectangle, with (x, R) = (x_t, y_t): 
</b></font></font>



0 &lt;=  col_x &lt;= (screenWidth   - 1) ) ;  x_min_t &lt;= x_t &lt;= x_max_t
0 &lt;=  row_y &lt;= (screenHeight  - 1) ) ;  y_min_t &lt;= y_t &lt;= y_max_t


	x_t = x_min_t + ( ( x_max_t - x_min_t )  / (screenWidth   - 1) ) * col_x ;
	y_t = y_min_t + ( ( y_max_t - y_min_t )  / (screenHeight  - 1) ) * row_y ;


	width_t  = x_max_t - x_min_t;
	height_t = y_max_t - y_min_t;



	x_t = x_min_t + ( width_t   / (screenWidth   - 1) ) * col_x ;
	y_t = y_min_t + ( height_t  / (screenHeight  - 1) ) * row_y ;

	normalized_width_t  = width_t  / (screenWidth  - 1);
	normalized_height_t = height_t / (screenHeight - 1);

	x_t = x_min_t + normalized_width_t  * col_x ; col_t = (x_t - x_min_t)/normalized_width_t;
	y_t = y_min_t + normalized_height_t * row_y ; row_t = (y_t - y_min_t)/normalized_height_t;


	rate_t = y_min_t + normalized_height_t * row_y
 ==  y_min_t + (y_max_t - y_min_t) * ( row_y / (screenHeight-1) )



<font color="#ce181e"><font size="4" style="font-size: 16pt"><b>Computation:
</b></font></font>

The GNU Multiple Precision Arithmetic Library, with a precision of
400 decimal points, is used to computationally generate the sequence
{( x<sub>0</sub>, R ), ( x<sub>1</sub>, R ), …, ( x<sub>1000</sub>, R ), ( x<sub>1001</sub>, R ), …, (
x<sub>last</sub>, R )}. WARNING: x<sub>last</sub> may be such that &quot;last&quot; is on
the order of a million [or more, depending on how you have things set
up]. For example, if you have zoomed in by a factor of one million
then MOST of the computed points (x, R) will NOT satisfy x_min_t &lt;=
x &lt;= x_max_t, and WILL NOT SHOW UP ON YOUR PLOT. You may need a
large sample size to get a satisfactory number of points to fall
inside your zoomed-in region. Although this calculation is
multi-threaded, it may still take some time to complete a figure.  These
 calculations were performed using 27 threads on a ‘16 core’ 2950X.

This project is a "work in progress," and requires sufficient patience and prior knowledge to build. This [fedora or ubuntu] linux program uses libraries from Qt, png, gmp, mpfr, range-v3, nlohmann/json, QJsonModel, RxCpp and 'toot', among others; source code is included for the latter three [the latter five may be found on github]. 

For example, on Ubuntu try

apt install libpng-dev libpng16-16

apt install librange-v3-dev

apt install libgmp-dev libmpfr-dev libmpfrc++-dev

//JSON for Modern C++ https://nlohmann.github.io/json/

git clone https://github.com/nlohmann/json.git

    cd json; mkdir build; cd build; cmake ..; cmake --build . ; sudo make install
  

<h1>License </h1>
<b>Logistic_Map</b> is copyright © 2019+ Patrick L. Nash and released under the MIT license
