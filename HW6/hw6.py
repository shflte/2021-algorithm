fin = open("input.txt", "r")
fout = open("output.txt", "w")

MiehPu = {}

for line in fin:
    word = line.split()
    if word[0] == "INSERT":
        key = word[1][4:len(word[1])]
        value = word[2][6:len(word[2])]

        if MiehPu.get(key) != None:
            fout.write("INSERT " + key + " FAIL!\n")
        else:
            MiehPu[key] = value
            fout.write("INSERT " + key + " SUCCESS!\n")

    elif word[0] == "FIND":
        key = word[1][4:len(word[1])]

        if MiehPu.get(key) == None:
            fout.write(key + " NOT FOUND!\n")
        else:
            fout.write("FIND " + key + ":" + MiehPu[key] + "!\n")
        
    elif word[0] == "ERASE":
        key = word[1][4:len(word[1])]

        if MiehPu.get(key) != None:
            MiehPu.pop(key)
            fout.write("ERASE " + key + " SUCCESS!\n")
        else:
            fout.write("ERASE " + key + " FAIL!\n")

    elif word[0] == "ENUM":
        key1 = word[1][4:len(word[1])]
        key2 = word[2][4:len(word[2])]
        index1 = 0
        index2 = 0

        keylist = sorted(list(MiehPu.keys()))

        if MiehPu.get(key1) == None:
            index1 = 0
        else:
            index1 = keylist.index(key1)

        if MiehPu.get(key2) == None:
            index2 = len(MiehPu) - 1
        else:
            index2 = keylist.index(key2)

        for i in range(index1, index2 + 1):
            fout.write("ENUM " + keylist[i] + ":" + MiehPu[keylist[i]] + "\n")
        
    elif word[0] == "CLEAR":
        MiehPu.clear()

fin.close()
fout.close()