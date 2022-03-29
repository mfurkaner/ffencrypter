# TXTEncryptor

This software now supports multiple encryption layers! <br />

When using the first time, <br />
-> install cmake to build and run the app
-> use bash scripts in scripts/ directory for convenience. <br />

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
