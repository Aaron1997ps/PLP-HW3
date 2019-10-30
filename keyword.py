import sys
#import os

class AArray(object):
    def __init__(self, maxSize):
        self.maxSize = maxSize
        self.elements = [None for _ in range(maxSize)]
        self.currentSize = 0

    def resize(self, newSize):
        if self.currentSize > newSize:
            self.currentSize = newSize

        newArray = [None for _ in range(newSize)]
        for x in range(self.currentSize):
            newArray[x] = self.elements[x]

        self.elements = newArray

    def addElement(self, elementToAdd):
        if self.currentSize == self.maxSize:
            print("ERROR------------------------------\n"
                  "AArray with size " + str(self.maxSize) + " tried to add a new element when it was already full.")
            return
        self.elements[self.currentSize] = elementToAdd
        self.currentSize += 1

    @property
    def size(self):
        return self.currentSize;

    def __getitem__(self, item):
        return self.elements[item]

    def __repr__(self):
        string = "["
        if self.currentSize > 0:
            for i in range(self.currentSize-1):
                string += str(self.elements[i])+", "

            string += str(self.elements[self.currentSize-1])
        string += "]"
        return string

    @property
    def returnList(self):
        return self.elements[:self.currentSize]





def formatFileIntoWords(filePath):
    fileContent = open(filePath).read()

    # Remove End-Lines if needed
    formatedData = fileContent.lower().replace("\n", " ")

    # Remove non-letter characters from a string
    def removeNonChars(text):
        if len(text) > 1:
            half = len(text)//2
            return removeNonChars(text[:half]) + removeNonChars(text[half:])
        if text[0] in ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", " "]:
            return text[0]
        else:
            return ""
    formatedData = removeNonChars(formatedData)

    # Remove Extra Spaces
    while "  " in formatedData:
        formatedData = formatedData.replace("  ", " ")

    formatedData = formatedData.split(" ")
    returnArray = AArray(len(formatedData))
    for s in formatedData:
        returnArray.addElement(s)

    return returnArray

def outputWithK(filePath, wordTouples, k):
    outputFile = open(filePath, 'w')

    if len(wordTouples) == 0:
        print("Word Touple was empty")
        outputFile.close()
        return

    totalOutput = 0
    currentCountVal = wordTouples[0][1]
    currentPos = 0
    while(totalOutput < k):

        outputFile.write(wordTouples[currentPos][0] + " " + str(wordTouples[currentPos][1]) + '\n')

        if currentCountVal != wordTouples[currentPos][1]:
            currentCountVal = wordTouples[currentPos][1]
            totalOutput += 1

        currentPos += 1
        if currentPos == len(wordTouples):
            outputFile.close()
            return

    outputFile.close()

def sortArray(ToupleList, mostFrequent):
    # I used a merge sort for this algorithm

    ListSize = len(ToupleList)

    if ListSize == 1:
        return ToupleList


    # Get Left and Right
    mid = ListSize//2

    left = sortArray(ToupleList[:mid], mostFrequent)
    right = sortArray(ToupleList[mid:], mostFrequent)

    # Merge
    wholeArray = [None] * ListSize
    LL, RL, l, r = len(left), len(right), 0, 0  # Set Left and Right Length, l and r are position counters
    TL = LL + RL  # Total Length of Array
    for i in range(TL):
        # Should it pull the right?
        if l == LL or (r != RL and ((((left[l][1] < right[r][1]) == mostFrequent) and not (left[l][1] == right[r][1])) or (left[l][0] > right[r][0] and (left[l][1] == right[r][1])))):
            wholeArray[i] = right[r]
            r += 1
            continue

        # If not, pull the left
        wholeArray[i] = left[l]
        l += 1

    return wholeArray

def capital(words):
    fixword = ''
    chars = list(words)
    for x in chars:
        n = ord(x) - 32
        fixword = fixword + chr(n)
    return fixword


def counting(words):
    coun = [1] * len(words)
    wordList = list(map(lambda x, y: (x, y), words, coun))
    return wordList
def getStopwords():
    return open("stopwords.txt").read().splitlines()

# Main Program Here
def topKWords():
    # Get Arguments
    if len(sys.argv) <= 1:
        print("Expected arguments: input, K, mostfrequent, uppercase, output\nSee readme for more details.")
        return -1

    print("Arguments: " + sys.argv[1])
    try:
        args = sys.argv[1].split(";")
        print(args)
        inputPath = args[0][6:]
        K = int(args[1][2:])
        mostFrequent = args[2][13:]
        uppercase = args[3][10:]
        outputPath = args[4][7:]
    except:
        print("Input Error Occurred\nParameters should be \"input=;k=;mostfrequent=;uppercase=;output=\"")
        return -2

    wordList = formatFileIntoWords(inputPath)

    stopwords = getStopwords()
    wordList = [x for x in wordList if x not in stopwords]

    if uppercase == "Y":
        wordList = list(map(capital, wordList))

    wordCount = counting(wordList)

    wordTouples = [(word, sum([x for w, x in wordCount if w == word])) for word in set([k for k, v in wordCount])]

    wordTouples = sortArray(wordTouples, mostFrequent == "Y")

    outputWithK(outputPath, wordTouples, K)


# Run Program
topKWords()

