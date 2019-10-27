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

def sortArray(array):
    # I used a merge sort for this algorithm

    if array.size == 1:
        return array

    # Get Left and Right
    mid = array.size//2

    leftArray = AArray(mid+1)
    for i in range(0, mid):
        leftArray.addElement(array[i])
    left = sortArray(leftArray)

    rightArray = AArray(mid+1)
    for i in range(mid, array.size):
        rightArray.addElement(array[i])
    right = sortArray(rightArray)

    # Merge
    wholeArray = AArray(array.size)
    LL, RL, l, r = left.size, right.size, 0, 0  # Set Left and Right Length, l and r are position counters
    TL = LL + RL  # Total Length of Array
    for i in range(TL):
        # Should it pull the right?
        if l == LL or (r != RL and left[l] < right[r]):
            wholeArray.addElement(right[r])
            r += 1
            continue

        # If not, pull the left
        wholeArray.addElement(left[l])
        l += 1

    return wholeArray


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
        mostFrquent = args[2][13:]
        uppercase = args[3][10:]
        outputPath = args[4][7:]
    except:
        print("Input Error Occurred\nParameters should be \"input=;k=;mostfrequent=;uppercase=;output=\"")
        return -2


# Test Functions

array = AArray(100)
print(array)
for i in [2, 5, 3, 1, 5, 2, 3, 8, 9]:
    array.addElement(i)
print(array)
print(sortArray(array))
# Run Program
topKWords()

