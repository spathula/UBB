import datetime
class Student():

    def __init__(self, studentID, name, group):
        self.__studentID = studentID
        self.__name = name
        self.__group = group

    def get_id(self):
        return self.__studentID

    def get_name(self):
        return self.__name

    def get_group(self):
        return self.__group

    def set_studentID(self, studentID):
        self.__studentID = studentID

    def set_name(self, name):
        self.__name = name

    def set_group(self, group):
        self.__group = group

    @staticmethod
    def read_student(line):
        parts = line.split(",")
        return Student(int(parts[0].strip()) , parts[1].strip() , int(parts[2].strip()))

    @staticmethod
    def write_student(student):
        return str(student.__studentID) + "," + student.__name + "," + str(student.__group)

    @staticmethod
    def read_student_pickle(student):
        if len(student) == 3:
            return Student(int(student[0]), student[1], int(student[2]))

    def __eq__(self , other):
        return self.__studentID == other.__studentID

    def __str__(self):
        return "ID: " + str(self.__studentID) + " | Name: " + self.__name + " | Group: " + str(self.__group)

class Assignment():

    def __init__(self , assignmentID , description , deadline):
        self.__assignmentID = assignmentID
        self.__description = description
        self.__deadline = deadline

    def get_id(self):
        return self.__assignmentID

    def get_description(self):
        return self.__description

    def set_name(self, description):
        self.__description = description

    def get_deadline(self):
        return self.__deadline

    @staticmethod
    def read_assignment(line):
        parts = line.split(",")
        deadline = datetime.datetime(int(parts[2].strip()) , int(parts[3].strip()) , int(parts[4].strip()))
        return Assignment(int(parts[0].strip()) , parts[1].strip() , deadline)

    @staticmethod
    def write_assignment(assignment):
        return str(assignment.__assignmentID) + "," + assignment.__description + "," + str(assignment.__deadline)

    @staticmethod
    def read_assignment_pickle(assignment):
        if len(assignment) == 3:
            year, month, day = assignment[2].split("-")
            day = day.split(" ")
            day = day[0]
            return Assignment(int(assignment[0]), assignment[1], datetime.datetime(int(year), int(month), int(day)))

    def __str__(self):
        return "ID: " + str(self.__assignmentID) + " | Description: " + self.__description + " | Deadline: " + str(self.__deadline)

    def __eq__(self , other):
        return self.__assignmentID == other.__assignmentID

class Grade():

    def __init__(self , studentID, assignmentID , grade):
        self.__assignmentID = assignmentID
        self.__studentID = studentID
        self.__grade = grade

    def get_grade(self):
        return self.__grade

    def get_assignmentID(self):
        return self.__assignmentID

    def get_studentID(self):
        return self.__studentID

    def __str__(self):
        return "StudentID: " + str(self.__studentID) + " | AssignmentID: " + str(self.__assignmentID) + " | Grade: " + str(self.__grade)

    @staticmethod
    def read_grade(line):
        parts = line.split(",")
        return Grade(int(parts[0].strip()) , int(parts[1].strip()) , int(parts[2].strip()))

    @staticmethod
    def write_grade(grade):
        return str(grade.__studentID) + "," + str(grade.__assignmentID) + "," + str(grade.__grade)

    @staticmethod
    def read_grade_pickle(grade):
        if len(grade) == 3:
            return Grade(int(grade[0]), int(grade[1]), int(grade[2]))
