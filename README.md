# keystore-shim
A "shim" for loading keystore data for later manipulation using native jni so you don't need to bother with Dalvik/Android/Java junk.

I didn't include much/any parsing of the keystore since that is an exercise left to the reader/coder. I only needed to confirm a few things on my end and it shouldn't be hard for anyone who understands the code to go futher. I'm mainly open sourcing this because @nelenkov asked nicely :)
https://twitter.com/kapitanpetko/status/907772363357380608

The code look familiar? It should - I stole it from my other project https://github.com/rednaga/native-shim :D

Usage
----------
Switch to the applications user id (on a root device, `su`, on a non-rooted make the application debuggable and use `run-as`. Then run the shim code after compiling and pushing it to the device, giving it the alias name as an argument:


What it will look like if it worked;
```
sailfish:/ $ ./data/local/tmp/shim realkeystorename
[*] keystore-snag - diff
 [+] Initializing JavaVM Instance
 [+] Initialization success (vm=0xec7191e0, env=0xec934230)
 [+] Found 'java.security.KeyStore' class (0xdb9)
 [+] Found getDefaultType method (0x702e3f4c)
 [+] Found default type of [ BKS ]
 [+] Found getInstance method (0x702e3f6c)
 [+] Retreived instance (0xdd5)
 [+] Found getEntry method (0x702e40cc)
 [+] Got KeyStore data (0xdf9)
```

You'll get an error if the KeyStore data isn't found.
```
sailfish:/ $ ./data/local/tmp/shim fakekeystorename                                                                                                      
[*] keystore-snag - diff
 [+] Initializing JavaVM Instance
 [+] Initialization success (vm=0xe76991e0, env=0xe78b4230)
 [+] Found 'java.security.KeyStore' class (0xdb9)
 [+] Found getDefaultType method (0x702e3f4c)
 [+] Found default type of [ BKS ]
 [+] Found getInstance method (0x702e3f6c)
 [+] Retreived instance (0xdd5)
 [+] Found getEntry method (0x702e40cc)
 [!] Error getting KeyStore data!
```


Disclaimer
----------

This code is meant for education and research purposes only. Do as you please with it, but accept any and all responsibility for your actions. The tools were created specifically to assist in malware reversing and analysis - be careful.


License
-------

    Copyright 2017 Tim 'diff' Strazzere <strazz@gmail.com>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.