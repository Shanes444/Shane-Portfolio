
"""
Created on Sun Sep  1 19:25:21 2024

@author: Shane Stevens
"""

profiles = open("Profiles.txt", "r", encoding="latin_1")
experts = open("Experts.txt", "r", encoding="latin_1")

scholars = {}

def populate_dict():
    line_num = 0

    last_name = ""
    first_name = ""
    full_name = ""
    id = 0
    school =""
    profiles_line = ""
    profiles_col = 0
    profiles.readline()
    
    for line in experts:
        if line_num != 0:
            line = line.replace('"', '')
            column = 0
            word = ""
            for char in line:
                if char == "\t":
                    if column == 0:
                        id = int(word)
                    elif column == 1:
                        last_name = word
                    elif column == 2:
                        first_name = word
                    elif column == 5:
                        if "Computer Science" in word:
                            school = word.split(",")[0]
                            if school not in scholars.keys():
                                scholars.update({school:{}})
                            full_name = first_name + " "  + last_name
                            areas = []
                            cur_id = id
                            while cur_id <= id:
                                profiles_word = ""
                                profiles_col = 0
                                if profiles_line != "":
                                    for char in profiles_line:
                                        if char == "\t":
                                            if profiles_col == 0:
                                                cur_id = int(profiles_word)
                                            elif profiles_col == 2:
                                                if cur_id == id:
                                                    areas.append(profiles_word)
                                            profiles_word = ""
                                            profiles_col += 1
                                        elif char == "\n":
                                            profiles_line = ""
                                        else:
                                            profiles_word+=char
                                else:
                                    profiles_line = profiles.readline().replace('"','')
                            scholars.get(school).update({full_name:areas})
                    word = ""
                    column+=1
                else:
                    word+=char
                
        line_num+= 1

    
def search_dict():
    print("             Welcome to the NC Scholar System")
    cont = 'c'
    school = ""
    area = ""
    partial_match = ""
    split_area = []
    output_scholars = []
    perfect_match = False
    match_count = 0
    max_match_count = 0
    while cont == 'c':
        perfect_match = False
        print("We currently include scholars from the following institutes:")
        print(*scholars.keys(), sep =",")
        print("")
        cont = "false"
        school = input("Select an institute: ")
        if school in scholars.keys():
            print(school + " has the following scholars in computer science:")
            for scholar in scholars.get(school).keys():
                print(scholar)
            print("")
            area = input("Input an area of study: ")
            for scholar in scholars.get(school).keys():
                if area in scholars.get(school).get(scholar):
                    output_scholars.append(scholar)
                    perfect_match = True
            if perfect_match == True:
                for output in output_scholars:
                    print("\t" + output)
            else:
                split_area = area.split()
                
                for scholar in scholars.get(school).keys():
                    partial_match = ""
                    max_match_count = 0
                    for areas in scholars.get(school).get(scholar):
                        match_count = 0
                        for word in split_area:
                            if word in areas:
                                match_count += len(word)
                                if match_count > max_match_count:
                                    max_match_count = match_count
                                    partial_match = scholar + " (" + areas + ")" 
                    if partial_match != "":
                        output_scholars.append(partial_match)
                if output_scholars != []:
                    print("There is no exact match, but we found some scholars that study similar areas:")
                    print(*output_scholars, sep ="; ")
                else:
                    print("There is no one that studies " + area)
        output_scholars = []
        print("")
        cont = input("Press c to continue or press anything else to quit: ")
        if cont == 'c':
            print(" ")
    print("Thank you for using the system!")
    
        
populate_dict()
search_dict()

profiles.close()
experts.close()
