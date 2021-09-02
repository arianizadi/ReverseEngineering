## CrackMe - Easy_One by Scifi

**Platform - C/C++ for OS X** </br>
**Link - https://crackmes.one/crackme/5d443bb533c5d444ad3018b3**

### 1. First Run Analysis

> First look should always be running the program.
>
> > Assuming it is not malicious.

<img src="https://ariandev.com/Github_Assets/CrackMe_Solutions/CrackMe-1/firstRun.gif" style="max-width: 40vw"></img>

> We can see that it is asking for a password. Next we enter some password so maybe we can get lucky. Unfortunately our attempt did not work :( But we can see a string that it returns saying "wrong password". It is important to look for string or certain build in functions the program uses to orient yourself when decompiling later.

#### Important Information Noticed

- Strings
  - "Enter the password..."
  - "wrong password"
- Functions
  - Printing Text
  - Getting User Input

### 2. Decompiling

> Today I am going to use [Hopper Disassembler](https://www.hopperapp.com/). I love hopper, but ghidra will also be able to accomplish the same. Both have great pseudocode options that come in very handy. Remember the checklist above of important information. This will be used later to orient ourselves in the decompiler view because it can be quite hectic at times to know whats going on. These so called monuments are there to help us know exactly where we are or what to expect.

#### Procedures

> Looking at the left we can see a tab saying Proc. for procedures used in the executable, looking here we can see some functions that are familiar.

| Function         | Information                              |
| ---------------- | ---------------------------------------- |
| \_main           | common start function for C/C++ programs |
| \_wrong_password | could be useful to look into             |
| fgets            | gets user input                          |
| printf           | print to screen                          |
| strcspn          | gets first value of char array           |
| strlen           | gets length of char array                |

<img src="https://ariandev.com/Github_Assets/CrackMe_Solutions/CrackMe-1/procedures.png" style="height: 70vh"></img>

#### Strings

> Strings are often obfuscated making it so a lot more annoying to figure out whats going on. This is also when procedures are the most important. In this case the strings are not encrypted ;).

| String Found                    | Information                             |
| ------------------------------- | --------------------------------------- |
| Enter the password...\n         | string we saw! Asking user for password |
| Correct!\nthe password is: %s\n | we want this string to print :)         |
| wrong password\n                | we do not want this string to print :/  |

<img src="https://ariandev.com/Github_Assets/CrackMe_Solutions/CrackMe-1/strings.png" style="height: 70vh"></img>

#### Commenting and Understanding

> Below is a video of me going through the decompiled binary and reading the values trying to understand what is going on with the information we know. Just to be clear it took me a lot longer to understand what is going on, I recorded this after I knew I was correct so if it takes longer don't worry it was hard for me too. We are only beginners, for now at least ;). It is helpful to know ASM and it's conventions or you will not be able to understand what is going on.

https://user-images.githubusercontent.com/15961653/131776426-4b079b6c-5802-4fca-90ea-9091571cadaf.mp4

### 3. Testing

> Finally, we have gotten to the final step in this CrackMe. I am sure the person who created it was not expecting such a long and involved explanation, but as I was learning I wished someone made something this in-depth that was current. Love u Lena and R4ndom u guys taught me everything. Anyway here we go let's test it! Remember what parameters we found in the code to make a valid key.

##### Rules for Key

1. Length must be equal to 10.
2. First and Last character must be equal.

<img src="https://ariandev.com/Github_Assets/CrackMe_Solutions/CrackMe-1/finalRun.gif" style="max-width: 40vw"></img>

### Closing Remarks

> Thank you for reading and following me on this journey! You will see more write ups from me soon! Something I want to leave here so we can come back and look in future endeavors is the levels of patching, by **The King of R4ndom**! There are **4** Levels of patching.

1. LAME - Localized Assembly Manipulation and Enhancing
2. NOOB - Not Only Obvious Breakpoints
3. SKILLED - Some Knowledge In Lower Level Engineered Data
4. SK1LL$ - Serial Keygenning In Low-level Languages, Stupid

> LAME - finding the jump that will make or break the check and either overwriting with a NOP, No Operation, or forcing a jump to go where you want. <br/><br/>
> NOOB - having a breakpoint in the routine that conducts the key check and every time it is called you are there to change the outcome. <br/><br/>
> SKILLED - going through each routine to know exactly what is going on line by line. This is a very good way to learn, but takes a lot more time. <br/><br/>
> SK1LL$ - the holy grail. This is essentially what we did earlier by looking at how the key is being made and producing one ourselves.

**Looking for more friends on github so follow me so you can stay up to date and I can see some of your projects! Until next time :wave:**
