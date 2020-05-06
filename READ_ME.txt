READ_ME for Cheaters Project:

1. To get the program to work, you must put the main.cpp, hashTable.cpp and hashTable.h files into one directory in
   Linux. Also, put the directory containing the files that are to be checked for plagiarism into this directory as well.
2. Once all the files are put into the same directory, type 'module load gcc' into the command line to ensure
   the C++ code will compile and work
3. Type 'make' into the command line to compile and link all the projects together.
4. If you do 'ls' in the command line there should be a file named 'plagiarismCatcher'. This is the executable for the
   program.
5. In the command line now you will run the program with the following command:

	./plagiarismCatcher nameOfFileDirectory wordChunkSize cheatingScoreCutoff
	
	a) plagiarismCatcher is the executable file that was made in Step 3.
	b) nameOfFileDirectory is the directory that contains the files that are to be checked for plagiarism that was
	   inserted into the main project directory in Step 1. Make sure to NOT put a backslash after the directory name
           as the program will not work.
	c) wordChunkSize is the number of words that will be taken from the file and tested against other files during
	   each pass of the program. EX: If wordChunkSize = 6 then every chunk taken from the file will be 6 words long	
	   and that will be used in the hashtable.
	d) cheatingScoreCutoff is the number that will determine whether a pair of files will the printed onto the screen
           because they are too similar. EX: If the cheatingScoreCutoff is 200 then any pair of files that share 200	
           of more common phrases as deemed by the hash table will be printed on the screen.

	Example Call: ./plagiarismCatcher sm_doc_set 6 200

This program make use of a two dimensional array of linked lists as a Hash Table. Each of the elements of the hash Table
are set to nullptr and a constant file number of -1. When a new node is added to an element in the hash table, it adds
to the head of the hash table or the node containing the -1 filenumber.

There is another two dimensional array of ints that is used to determine the number of similarities between two files.
A function is used to traverse all the linked lists in the hash table and when two files have the same key value, the
function increases the number in the 2-D array corresponding the two file numbers. For example, say there is a 25 x 25 array. 
In the linked list the files 3 and 14 have a similarity. In the array, the element corresponding to row 3 and col 14 will
be incremented by 1.

Finally, the program will find the pairs of files that have a higher value that the cheatingScoreCutoff. These Nodes are put
into a vector for temporary storage. Once all the cheaters are found, that vector goes to another function that sorts
out cheaters will the highest score being first. Finally, the cheaters are printed onto the screen with their score and
file numbers.

The Program would have worked successfully if the final two lines are 'Program Done' and 'Destructor Finished'.  