## Loader models
  - We have created loader models for the types of resources that can be loaded.

## The actual loader
  - We have now created the basic loader class which will manage the resources that have been loaded
  - now we can add or remove items from the respective resource container
  - so now we have the functionality to edit the files if needed.
  - we also need to be able to get constant access to the resource vectors
  - so lets do the functions needed to retrieve the vectors of resources that are currently available
  - once a file has been parsed the resource data will be stored in the vectors
  - so we can simply load a file and use these get methods to obtain the contents of the vectors
  - so lets get to making the getter functions

  - the functions to get the respective resource has been added.
  - it has been made constant so that the reference will not allow them to make changes directly but instead will have to use the API provided by the class

  - now the only thing remaining is to be able to parse a file that will contain the resource information.
  - the reason it has been delayed is that it is by far the most non-trivial and also since the format for the file has not been decided yet.
  - so now we have to decide on the format for the file
  - the file is in binary.
  - let now just think how we are going to structure the data to be able to easily write to and also to parse them.

  - the main data of the file is the actual vectors containing the data.
  - can we actually just simply write() the vector itself or do we need to loop through the vector and write() each object?
  - let see if it works with just writing the vector itself first, otherwise we will write once by once.
  - if we can write the vector then we can simply write the vector in a specific order and not worry about any metadata,
  - if it has to be written one by one then we will need give metadata of its size also and anything else i might have forgotten.

  - first we are going to try with only the vectors
  - so we are simply going to write the vectors into the file and try to read it
  
  - now that i think about it, there is no mechanism to actually create or save the file.
  - so now we need to create a functions to save the data into a file.
  - apparantly writing of vector is crap. so we have to do writing one by one

  - the loading and saving of the data is completed.
  - the resources available currently are textures animations and other loader files.
  - this can now be used temporarily and expanding to other resources is going to be easy now