import csv

addressesFile = open('san_joaquin.csv', 'r')
parsedFile = open('coords.txt', 'w')

csv_reader = csv.reader(addressesFile, delimiter=',')
line_count = 0
for line in csv_reader:
    if line_count != 0:

        addressModified = str(line[0]) + "," + str(line[1])
        parsedFile.write(addressModified + "\n")
        line_count += 1
    
    if line_count == 0:
        line_count += 1

print('Lines processed:', line_count)
