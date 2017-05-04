#encoding:UTF-8
import sys
from time import time

wordTree = [None for x in range(256)]
wordTree.append(0)
nodeTree = [wordTree, 0]

def createWordTree(sensitive_file):
    awords = []
    for b in open(sensitive_file, 'rb'):
        awords.append(b.strip())

    for word in awords:
        temp = wordTree
        for a in range(0,len(word)):
            index = ord(word[a])
            if a < (len(word) - 1):
                if temp[index] == None:
                    node = [[None for x in range(256)],0]
                    temp[index] = node
                elif temp[index] == 1:
                    node = [[None for x in range(256)],1]
                    temp[index] = node

                temp = temp[index][0]
            else:
                temp[index] = 1


def searchWord(str):
    temp = nodeTree
    word = []
    a = 0
    while a < len(str):
        index = ord(str[a])
        temp = temp[0][index]
        if temp == None:
            temp = nodeTree
            a = a - len(word)
            word = []
        elif temp == 1 or temp[1] == 1:
            word.append(index)
            return True
        else:
            word.append(index)
        a = a + 1

    return False


if __name__ == '__main__':
    createWordTree("words.txt");
    while True:
        word = input("> ")
        if searchWord(word):
            print '******'
        else:
            print word


