In this iteration, a process is made up for each directory which will contain several HTML files.  Then  that process will generate two other 
processes. One process  will read the all html files isolate the body parts of  the  each  HTML  file  and  remove  all  HTML  tags  and  escapes.  The 
resultant phrases in the each HTML file are merged. The merged output is a standard output and it send  to  a file descriptor  through  “dup2”.  Then 
the output is returned to the first process through unnamed pipeline.
Then the resultant output of the above mentioned process is send to a  file descriptor  and the  file  descriptor  send  through the unnamed 
pipeline  to  the  3rd process  which  will  calculate  the  frequencies  of  the words using the code  implemented  in the  iteration  1.  The  received  file 
descriptor convert to the  standard input using  “dup2”. Then the output of this process is standard output and again it send to a file descriptor as 
mentioned  above. Then  it will again send to the 1st process through the unnamed pipeline.
After that the output from the  1st process  will be send to another process  using unnamed pipe  which  connected  to  another two processes,again using unnamed pipe. One of those two is a global hash table and the other one is creating a SVG file
