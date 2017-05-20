# Python script to check the results of fraud detector tests
import sys
import sys
import string

resultFile = sys.argv[1]
correctFile = sys.argv[2]

# Read the results file into a list
with open(resultFile) as f:
    result_lines = f.read().splitlines()

# Read the correct file into a list
with open(correctFile) as g:
    correct_lines = g.read().splitlines()

# Sanity check to make sure each line was read correctly
print 'Number of results read: ' + str(len(result_lines))
print 'Number of corrects read: ' + str(len(correct_lines))

# Make sure strings are in the correct format
results_stripped = map(str.strip, result_lines)
correct_stripped = map(str.strip, correct_lines)

# Now compare elements of each list one by one
num_matches = 0
num_total = len(results_stripped)
for i in range(num_total):
    result = results_stripped[i]
    correct = correct_stripped[i]
    if result == correct:
        num_matches = num_matches + 1

print 'Number of matches: ' + str(num_matches)
correct_proportion = float(num_matches) / float(num_total)
print 'Percentage of correct results: ' + str(correct_proportion * 100) + '%'