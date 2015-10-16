## Fizzix: Functional Specifications ##
_The information in this document should be considered preliminary._

Fizzix is a Newtonian physics engine where laws can change according to user preference. We will hopefully be able to simulate real-world Newtonian physics with this engine with a default rule set, as well as intriguing forms of perverted physics using a modified rule set.

### Goals: ###
  1. Display a set of objects with an OpenGL interface.
  1. Display the current rule set to the user, and allow for modification of this rule set.
    1. Create and delete forces (i.e. gravity=GMMR^-2)
    1. Modify forces (i.e. gravity=GMMR)
    1. Create and delete object properties (i.e. mass)
    1. Modify the object properties in the system (i.e. mass is renamed mojo)
    1. Create and delete objects in the system (i.e. block A)
    1. Modify the properties of objects in the system (i.e. block A mass = 1g)
  1. Calculate the movement of the set of objects with the current rule set.
    1. Linear motion
    1. Rotational motion
    1. Collisions
    1. Complex rigid bodies
  1. Attempt to determine a rule set representing real-world Newtonian mechanics.

### Software Requirements: ###
Windows, Mac OS X or a POSIX-based operating system
Qt graphical toolkit

### User Interface ###
The user will see the main object area to display objects.
The user will also see a tabbed pane are in order to display forces, system properties and object properties.
To start the simulation, the user manually defines a scene or selects File->Load scene and the data is read from file. The user then presses the “Start” button.
Additionally, the user can File->Load laws in order to load a real-world rule set or a custom saved rule set.
A mockup is attached to this specification.

### Phases ###
  1. Create a Display Area
    1. The result of this phase will be a way to represent geometric properties of objects in code, and then in an OpenGL canvas.
  1. Create a Graphical Interface
    1. A form of representation of all the forces acting on an object.
    1. A form of representation of all the objects.
    1. The graphical interface to complete goals 2(a-f).
  1. Create a basic form of physics
    1. A form to represent all the moving properties of an object.
    1. Animate the objects moving.
    1. Program is now ready to be graded; the last part is nice if we get it.
  1. Find bugs. Really big ones.
    1. Figure out what we can not represent, and slowly implement it.

## Mockup ##
<img src='http://img223.imageshack.us/img223/8167/fizzixmockupmr6.png' alt='Free Image Hosting at www.ImageShack.us' border='0' />