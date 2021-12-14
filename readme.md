Github: https://github.com/ryanperryj/SimTree

Video:  https://pennstateoffice365-my.sharepoint.com/:v:/g/personal/rjp5603_psu_edu/EVtV1XLdPXBCqDLqxkwGh5MBR34zYiiV7cP4P_V4HYCW9g?e=llFjxU

Boost: https://www.boost.org/

Just build, making sure to include and link to boost, then run the executable. The program will prompt for multiple things:

1. Model choice
	Available models will be listed, select a model by just inputting it's number.
	
2. Parameter file choice
	The program will print a list of available files, and the user can select one by inputting it's number. if none exists then the 
	user can simply input a number to create a new template. The user will later be prompted to go and edit the file externally. 
	
3. Input file choice
	Works just like the parameter file choice, except for the fact that models are not required to have inputs. The Pendulum model
	has no inputs, and so the user will not be prompted to choose an input file.
	
4. Output file choice
	Select an existing file to overwrite it, or type a new number to output to a new file.

5. Simulation time input
	Enter how long to simulate for.
	
-----------------------------------------------------------------------------------------------------------------------------------------------
Some definitions:

* Parameter files are for data that will remain constant, the have one row of labels and one row of values, that's it.

* Input files work with a zero-order hold, meaning the input lasts from the t it is keyed at until the next input for that label. 
	Every input must be given a value at t = 0.
	
* Output files output first the parameter file and inputs with which it was generated, and then the outputs defined by the model.

* Vectors in the file have spaces in between each value.

-----------------------------------------------------------------------------------------------------------------------------------------------
Some Notes:

This application is not meant to be just a front end, the code is designed around the fact that the user will be working with it and 
adding or editing models. To add new models, a user has to create a class that inherits Model and create override all pure virtual 
functions.

An important design point is the fact that parameters, inputs, and outputs can be a variety of different types. This is highlighted in
the design of the ExampleModel. Data can be ints, floats, bools, strings, vectors of these and more. This is why there is some weird 
switch case stuff iand strings being passed around.

Please look at the Github for some example files.