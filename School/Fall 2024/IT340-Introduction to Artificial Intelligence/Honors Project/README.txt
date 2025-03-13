I fugured that since I didn't communicate at all while working on this program that I would at least
use this to explain my thinking while making this program.

I figured that since my idea of making a nlp model using bag of words would be very similar to the
midterm 2 assignment, that I would make my program different by trying to make it as scalable as possible.
In theory, my program should work with any amount of files with any amount of classes, assuming that the
folders are sorted correctly. I tested this program using 3 different data sets. The first one being
The spam data set used for midterm 2, the second being a set of presidential speeches that we used in
my machine learning class, and the 3rd being the previous 2 combined, which I used to test how it worked when
there were more than 2 classes.

I used Jupyter for this program because I found that I prefer ipynb files better for machine learning projects
such as this, since being able to test specific code segments at a time is extremely useful to me. This program is
somewhat based off of the midterm 2 assignment, albeit with some significant differences. I will now proceed to 
explain my program cell by cell.

The first cell is simply importing the packages that I used. I didn't use very many packages. I know that
scikit-learn is a very useful package for machine learning, in fact I used it for several assignments in my machine
learning class, but I decided not to use it, since I wanted to try to build the model without it.

The second cell is for the "settings" of the program. These include the folder being used for the data, the overall
percentage of the data used, the percentage of data that will be used for training and testing, and a list
of words that will be ignored during testing.

The third cell is for gathering the data from the text files. This part is similar to the first section of midterm
2, but I had to alter it to account for an unknown amount of classes. The first part gets the file names, while
the second part stores the text from the files in either the training set, or the testing set.

The fourth cell is for creating the dictionary that will store all of the words and the count for each word in the
training set.

The fifth cell is takes the testing data and predicts the class for the data. This is similar to midterm 2 again,
but I had to change it a bit to account for the possibility of the same word appearing multiple times. I also messed
around with using natural log to prevent getting 0 values, but I decided not to since it created a new problem
where there would be a lot of infinity values instead.

The last cell prints the number of true and false values for each class being used, and lastly, prints the
accuracy. My code is very inaccurate, usually scoring around .50. This would be the main thing that I would have
liked to fix with my code, but This whole program is kind of rushed since I forgot to do it until basically the
last minute, so there are definitely still a few rough edges. I found that the presidential_speeches data set had
the lowest accuracy, likely because it had the longest text, whicb increased the likelihood of 0 probabilities