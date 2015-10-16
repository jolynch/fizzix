### Flow of Program ###
  * Initialization
    * Initialize OpenGL
    * Create GUI objects
    * Display GUI objects
    * Create a FizData object to hold FizObject, FizForce and   FizProperty
    * Load realistic force set
    * Load realistic property set
  * User-GUI interaction
    * Upon creation of an object with the interface, create a FizObject
    * Upon creation of a new force, create a FizForce
    * Upon creation of a property, create a FizProperty
    * Upon modification of any existing data, lookup the corresponding FizObject/FizForce/FizProperty, and insert modifications.
    * Save any loaded configurations
    * Load any saved configurations
  * Runtime
    * Executed when user presses "Start"
      * Submit FizData pointer to Fizzix backend
      * Create thread to pull backend data
        * If new data are being written to FizData current, use old FizData
        * If new data are not being written and data do not match, copy current to old really quickly and execute a new step
        * Update updates-per-second counter
        * For each step:
          * Iterate FizObjects
          * Calculate FizForces
          * Move FizObjects
      * Create thread to draw backend data
        * Based on updates-per-second, decide number of times to draw.
        * Draw FizObjects
    * When user pauses or stops
      * Kill puller thread, lock FizData
      * Draw known FizData
  * Termination