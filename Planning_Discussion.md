Discuss!

Create a heading for any new discussions with == TOPIC NAME ==, then please put your initials and a date after your comments, just so it doesn't get too confusing...

--D.S. 2/5 22:04

## Logo ##

<img src='http://i43.tinypic.com/s3ztc0.jpg'> look good?<br>
<br>
-- P.P.B. 2/5 22:32<br>
<br>
Nice!  Also, I would suggest having the first F, with the vector thing, be our icon (plus a background and border, or something).<br>
<br>
--D.S. 2/5 22:47<br>
<br>
<h2>Ether</h2>

Alright, I thought it would be a good idea to impose a coordinate system on the objects, and allow it to interact with them, kinda.  For instance, this allows you to easily define which direction <0,0,-1> is in, and therefore creating a constant gravity function is incredibly easy, allowing a simulation of objects falling to Earth.<br>
<br>
This also allows for really easy air friction, by just having the objects constantly lose energy to the ether.<br>
<br>
Also, you can do some cool stuff with it like:<br>
<br>
Instead of gravity, two objects experience forces equal to the cross product of what gravity would have been with <0,0,1>, making stuff spin really fast around each other.  This is not possible without defining some coordinate system.<br>
<br>
I think this would be a neat idea to play around with, and not really hard to implement.<br>
<br>
--D.S. 2/5 22:43<br>
<br>
I mean, ultimately we have to be able to represent this is OpenGL's coordinate system.  I haven't done a whole lot with OpenGL, but from what I know they define Z coming out/into the screen and the xy like we usually use.  Do we really want to create a "local" coordinate system for each object?<br>
<br>
--J.L. 2/6 16:27<br>
<br>
Actually, its insanely easy to switch viewing systems - there is a matrix for this purpose lol.  The command glulookat will allow you to easily switch also, and is also what we will use for the camera changes.<br>
<br>
--D.S. 2/6 17:53<br>
<br>
<strike>I'm not entirely sure what you're suggesting. Are you suggesting a coordinate system in which to place objects and have stuff? Well, yeah, how else would you do any math? Or are you suggesting a coordinate system for each? Because that's not useful. Explain?</strike> Okay, so just universal, one-particle forces? That sounds fine.<br>
<br>
--P.P.B. 2/6 23:01<br>
<br>
<h2>Immovable Objects</h2>

Basically, I would suggest allowing people to add things that affect the system but aren't affected themselves.  This would make it easy to do a ground, for instance<br>
<br>
--D.S. 2/5 22:45<br>
<br>
Hm, I think that we need an area for feature requests.<br>
<br>
--J.L. 2/6 16:37<br>
<br>
<h2>Camera</h2>

Is spherical good?  As in, Up/Down changes phi, Left/Right changes theta, and PageUp/PageDown zoom in and out?<br>
<br>
--D.S. 2/5 22:50