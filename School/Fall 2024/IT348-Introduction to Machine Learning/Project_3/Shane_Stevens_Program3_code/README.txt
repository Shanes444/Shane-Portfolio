This program tests data from the given data set using the logarithmic model and the random forest model.
Running the code requires running all of the cells sequentially, with the exception of the boxes after
where it says "Only run one of the next two boxes", in which case only run one of the cells.
The first cell creates a testing and training set from the previously gathered data, while the second
uses the data already gathered as the training set, and the new data as the testing set. In the list
called "files" in cell 2, you enter the names of the files you want to use. If you want to use seperate
data as the testing set, then enter the files in the "files" list in the cell after the where it says 
"Only run one of the next two boxes". Since turning in the program, I fixed an error where I forgot to scale
the testing data, which was causing a high level of inaccuracy.