This is a simple C library aimed at parsing JSON files into structs

The project has three important components: 

The lexer, which converts the text file into a sequence of symbols.

The parser, which uses multithreading to concurrently construct multiple JSON objects/subobjects at the same time.

The JSON struct representation which allows for any type of JSON object to be stored in this format and then used in a conventional manner.

The representation uses a hash map to map a specific hash to a byte offset indicating where in the struct we are storing that value.
The value can then be decoded based on the value at that offset and returned to the user.