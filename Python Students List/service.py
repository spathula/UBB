from domain import Student , Assignment , Grade
from random import randint
import random
import datetime


class StudentService():

    def __init__(self , student_repository , student_validator , grade_repository):
        self.__student_repository = student_repository
        self.__student_validator = student_validator
        self.__grade_repository = grade_repository

    def add_student(self , studentID , name , group):
        student = Student(studentID , name , group)
        self.__student_validator.validate_student(student)
        self.__student_repository.add(student)

    def remove_student(self , studentID , dummy1 , dummy2):
        student = Student(studentID , None , None)
        removed_student = self.__student_repository.search(student)
        self.__student_repository.remove(student)
        grades = self.__grade_repository.get_all_grades_student(studentID)
        for grade in grades:
            self.__grade_repository.remove(grade)
        return removed_student.get_id() , removed_student.get_name() , removed_student.get_group()

    def update_student(self , studentID , update , dummy):
        searched_student = Student(studentID , None , None)
        student = self.__student_repository.search(searched_student)
        group = student.get_group()
        old_name = student.get_name()
        self.remove_student(studentID , None , None)
        self.__student_validator.validate_student(student)
        self.add_student(studentID , update , group)
        return old_name

    def get_all_students(self):
        return self.__student_repository.get_all_items()

    def get_group_students(self , groupID):
        required_list = []
        students = self.get_all_students()
        for student in students:
            if student.get_group() == groupID:
                required_list.append(student.get_id())
        return required_list

    def generate_students(self):
        groups = [915 , 916 , 917]
        for counter in range(5):
            name = ""
            first_names = ["Shivam" , "Courtney" , "Cairo" , "Ihsan" , "Ava" ,
                           "Maciej" , "Aadam" , "Sumaiya" , "Manha" , "Sammy" ,
                           "Tom"]
            last_names = [" Allan" , " Duffy" , " Winter" , " Mill" , " Patton" , " Tillman" , " Boo" , " Lam" ,
                          " Sawyer" ,
                          " Miranda" , " Ashley"]
            random = randint(0 , len(first_names) - 1)
            name += first_names[random]
            random = randint(0 , len(last_names) - 1)
            name += last_names[random]
            self.add_student(counter , name , groups[randint(0 , 2)])


class AssignmentService():

    def __init__(self , assignment_repository , assignment_validator , grade_repository):
        self.__assignment_repository = assignment_repository
        self.__assignment_validator = assignment_validator
        self.__grade_repository = grade_repository

    def add_assignment(self , assignmentID , description , deadline):
        assignment = Assignment(assignmentID , description , deadline)
        self.__assignment_validator.validate_assignment(assignment)
        self.__assignment_repository.add(assignment)

    def remove_assignment(self , assignmentID , dummy1 , dummy2):
        assignment = Assignment(assignmentID , None , None)
        removed_assignment = self.__assignment_repository.search(assignment)
        self.__assignment_repository.remove(assignment)
        grades = self.__grade_repository.get_all_grades_assignment(assignmentID)
        for grade in grades:
            self.__grade_repository.remove(grade)
        return removed_assignment.get_id() , removed_assignment.get_description() , removed_assignment.get_deadline()

    def update_assignment(self , assignmentID , update , dummy):
        searched_assignment = Assignment(assignmentID , None , None)
        assignment = self.__assignment_repository.search(searched_assignment)
        deadline = assignment.get_deadline()
        old_description = assignment.get_description()

        self.remove_assignment(assignmentID , None , None)
        self.__assignment_validator.validate_assignment(assignment)
        self.add_assignment(assignmentID , update , deadline)
        return old_description

    def get_all_assignments(self):
        return self.__assignment_repository.get_all_items()

    def generate_assignments(self):
        descriptions = ["Write an application that manages lab assignments for students at a given discipline." ,
                        "Write an application for movie rental." , "Write an application for a book library." ,
                        "The committee needs a program that will allow managing the list of scores and establishing the winners. " ,
                        "A family wants to manage their monthly expenses. In order to complete this task, the family needs an application to store, for a given month, all their expenses."]
        years = ["2020" , "2021" , "2019" , "2020" , "2021"]
        months = ["5" , "11" , "3" , "8" , "1"]
        days = ["30" , "11" , "3" , "5" , "13"]
        random.shuffle(descriptions)
        random.shuffle(years)
        random.shuffle(months)
        random.shuffle(days)
        for counter in range(5):
            deadline_year = years[counter]
            deadline_month = months[counter]
            deadline_day = days[counter]
            deadline = datetime.datetime(int(deadline_year) , int(deadline_month) , int(deadline_day))
            self.add_assignment(counter , descriptions[counter] , deadline)


class GradeService():

    def __init__(self , grade_repository , grade_validator , student_repository , assignment_repository):
        self.__grade_repository = grade_repository
        self.__grade_validator = grade_validator
        self.__student_repository = student_repository
        self.__assignment_repository = assignment_repository

    def give_assignment(self , studentID , assignmentID , grade):
        check_grades = self.__grade_repository.get_all_grades_student(studentID)
        for grade in check_grades:
            if grade.get_assignmentID() == assignmentID:
                raise ValueError("The student(s) already have that homework assigned!")
        grade = Grade(studentID , assignmentID , grade)
        student = Student(studentID , None , None)
        assignment = Assignment(assignmentID , None , None)
        self.__grade_validator.validate_grade(grade , self.__student_repository.check_existence(student) ,
                                              self.__assignment_repository.check_existence(assignment))
        self.__grade_repository.add(grade)

    def give_grade(self , studentID , assignmentID , grade):
        grade_to_give = Grade(studentID , assignmentID , grade)
        student = Student(studentID , None , None)
        assignment = Assignment(assignmentID , None , None)
        student_grades = self.__grade_repository.get_all_grades_student(studentID)
        for grade in student_grades:
            if grade.get_assignmentID() == assignmentID and grade.get_grade() == 0:
                self.__grade_repository.remove(grade)
                self.__grade_validator.validate_grade(grade_to_give ,
                                                      self.__student_repository.check_existence(student) ,
                                                      self.__assignment_repository.check_existence(assignment))
                self.__grade_repository.add(grade_to_give)
                return grade_to_give.get_studentID() , grade_to_give.get_assignmentID() , grade_to_give.get_grade()
            else:
                raise ValueError("The student doesn't have that homework or has already been given a grade!")

    def remove_assignment_given(self , studentID , assignmentID , grade):
        student_grades = self.__grade_repository.get_all_grades_student(studentID)
        for grade in student_grades:
            if grade.get_assignmentID() == assignmentID:
                self.__grade_repository.remove(grade)
                return grade.get_studentID() , grade.get_assignmentID() , grade.get_grade()

    def remove_grade(self , studentID, assignmentID, grade):
        student_grades = self.__grade_repository.get_all_grades_student(studentID)
        for grade in student_grades:
            if grade.get_assignmentID() == assignmentID:
                self.__grade_repository.remove(grade)
                return grade.get_studentID() , grade.get_assignmentID() , grade.get_grade()

    def students_with_assignment(self , assignmentID):

        grades_to_correct = self.__grade_repository.get_all_grades_assignment(assignmentID)
        grades = []
        for grade in grades_to_correct:
            if grade.get_grade() > 0:
                grades.append(grade)
        for first_counter in range(0 , len(grades) - 1):
            for second_counter in range(first_counter + 1 , len(grades)):
                if (grades[first_counter].get_grade() < grades[second_counter].get_grade()):
                    grades[first_counter] , grades[second_counter] = grades[second_counter] , grades[first_counter]
        return grades

    def late_students(self):

        current_date = datetime.datetime.now()
        students = self.__student_repository.get_all_items()
        output = ""
        for student in students:
            grades = self.__grade_repository.get_all_grades_student(student.get_id())
            for grade in grades:
                if grade.get_grade() == 0:
                    assignmentID = grade.get_assignmentID()
                    assignment_search = Assignment(assignmentID , None , None)
                    assignment = self.__assignment_repository.search(assignment_search)
                    if assignment.get_deadline() < current_date:
                        output += "\nStudent ID '" + str(student.get_id()) + "' is late handing the assignment " + str(assignment.get_id())
        return output

    def best_students(self):

        output = ""
        best_students = dict()
        students = self.__student_repository.get_all_items()
        for student in students:
            grades = self.__grade_repository.get_all_grades_student(student.get_id())
            if self.get_student_average(grades):
                best_students[student.get_id()] = self.get_student_average(grades)
            else:
                continue

        sorted_students = sorted(best_students.items() , key=lambda item: item[1] , reverse=True)

        for counter in range(len(sorted_students)):
            output += "\nStudent ID: " + str(sorted_students[counter][0]) + " | Average: " + str(sorted_students[counter][1])

        return output

    def get_student_average(self , grades):
        sum = 0
        counter = 0
        for grade in grades:
            sum += grade.get_grade()
            counter += 1
        if sum == 0:
            return
        return sum / counter
