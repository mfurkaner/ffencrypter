# TXTEncrypter
<br />
This software is an encrypt/decrypt engine with multiple layer of encryption using seeds and user identification.
<br />

# When using the first time, <br />
<br />
-> install cmake to build and run the app
-> use bash scripts in scripts/ directory for convenience. <br />

# Using TXTEncrypter with a config file
<br />
Create a file named 'config.in' using the following options  <br />
-> command = Command to run ( enc : encrypt, dec : decrypt ) <br />
-> filepath = Relative path of the file to encrypt/decrypt <br />
-> fileout = Relative path of the output file  <br />
-> id = Id of the encrypter  <br />
-> pass = Password of the encrypter <br />
-> addseed = Add a seed <br />
-> mangling = Enable/disable mangling ( 0 : disable, 1 : enable ) <br />
-> check = Enable/disable data loss check ( 0 : disable, 1 : enable ) <br />
-> add '\#' at the beginning of a line to ignore the line

# For manual use:

To encrypt a file <br />
<br />
-> use enc command <br />
-> enter id of encrypter and a password, this will be used to authenticate the decryption later. <br />
-> enter the path to the file <br />
-> enter a path for the encrypted output file  ( enter '.' to use default path ) <br />
-> enter how many layers of encryption you want <br />
-> enter a seed for each encryption layer <br />
-> you are good to go <br />

To decrypt a file <br />

-> use dec command <br />
-> enter id and password of the encrypter. If you fail at this step, application will not let you decrypt. <br />
-> enter the path to the file <br />
-> enter a path for the decrypted output file  ( enter '.' to use default path ) <br />
-> enter how many layers of encryption you want <br />
-> enter the seed for each decryption layer <br />

To find and print out differences between two files <br />

-> use pdif command <br />

To change the run settings ( Not implemented yet ) <br />

-> use settings command <br />
