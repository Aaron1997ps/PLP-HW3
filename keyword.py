import sys


def formatFileIntoWords(filePath):
    fileContent = open(filePath).read()

    # Remove End-Lines if needed
    formatedData = fileContent.lower().replace("\n", " ")

    # Remove non-letter characters
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

    return formatedData.split(" ")

def sortArray(array):
    # I used a merge sort for this algorithm

    if len(array) == 1:
        return array

    # Get Left and Right
    mid = len(array)//2
    left = sortArray(array[mid:])
    right = sortArray(array[:mid])

    # Merge
    wholeArray = []
    LL, RL, l, r = len(left), len(right), 0, 0  # Set Left and Right Length, l and r are position counters
    TL = LL * RL  # Total Length of Array
    for i in range(TL):
        # Should it pull the right?
        if l == LL or (r != RL and left[l] < right[r]):
            wholeArray.append(right[r])
            r += 1
            continue

        # If not, pull the left
        wholeArray.append(left[l])
        l += 1


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
        print("Input Error Occurred\nParameters hould be \"input=;k=;mostfrequent=;uppercase=;output=\"")
        return -2


# Test Functions

print(sortArray([2, 5, 3, 1, 5, 2, 3, 8, 9]))
# Run Program
topKWords()