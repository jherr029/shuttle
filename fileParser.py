import csv

addressesFile = open('san_joaquin.csv', 'r')
parsedFile = open('sampleAddresses.txt', 'w')

csv_reader = csv.reader(addressesFile, delimiter=',')
line_count = 0
for line in csv_reader:
    if line_count != 0 and line[2] != '':

        addressModified = str(line[3])
        addressModified = addressModified.replace(" ", "+")
        parsedFile.write(str(line[2]) + "+" + addressModified+ "\n")
        line_count += 1
    
    if line_count == 0:
        line_count += 1

print('Lines processed:', line_count)
