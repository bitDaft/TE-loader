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