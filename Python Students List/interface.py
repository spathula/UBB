from exceptions import RepoError , ValidError
import datetime


class Interface():

    def __init__(self , student_service , assignment_service , grade_service, undoredo):

        self.__student_service = student_service
        self.__assignment_service = assignment_service
        self.__grade_service = grade_service
        self.__undoredo = undoredo

    def manage_students(self):

        print("1. Add student.")
        print("2. Remove student.")
        print("3. Update student.")
        print("4. List students.")
        user_choice = int(input("\nSelect option >>> "))
        commands = {1: self.ui_add_student , 2: self.ui_remove_student , 3: self.ui_update_student ,
                    4: self.ui_list_students}
        commands[user_choice]()

    def ui_add_student(self):

        studentID = int(input("Insert the new student's ID >>> "))
        name = input("Insert the new student's name >>> ")
        group = int(input("Insert the new student's group >>> "))

        self.__student_service.add_student(studentID , name , group)
        print("Student added succesfully!")
        self.__undoredo.undo_operation(self.__student_service.remove_student, studentID, name, group)

    def ui_remove_student(self):

        studentID = int(input("Insert the student's ID that you wish to remove >>> "))

        removed_student_id, removed_student_name, removed_student_group = self.__student_service.remove_student(studentID, None, None)
        print("Student removed succesfully!")
        self.__undoredo.undo_operation(self.__student_service.add_student , removed_student_id, removed_student_name, removed_student_group)

    def ui_update_student(self):

        studentID = int(input("Insert the student's ID that you wish to update >>> "))
        update = input("Insert the new name for the student >>> ")

        old_name = self.__student_service.update_student(studentID , update, None)
        print("Student updated succesfully!")
        self.__undoredo.undo_operation(self.__student_service.update_student , studentID, old_name, update)

    def ui_list_students(self):

        students = self.__student_service.get_all_students()
        for student in students:
            print(str(student))

    def manage_assignments(self):

        print("1. Add assignment.")
        print("2. Remove assignment.")
        print("3. Update assignment.")
        print("4. List assignments.")
        print("5. Give assignment to a student.")
        print("6. Give assignment to a group.")
        user_choice = int(input("\nSelect option >>> "))
        commands = {1: self.ui_add_assignment , 2: self.ui_remove_assignment , 3: self.ui_update_assignment ,
                    4: self.ui_list_assignments , 5: self.ui_give_assignment_student , 6: self.ui_give_assignment_group}
        commands[user_choice]()

    def ui_add_assignment(self):

        assignmentID = int(input("Insert the new assignment's ID >>> "))
        description = input("Insert the new assignment's description >>> ")
        deadline_year = input("Insert the new assignment's year deadline >>> ")
        deadline_month = input("Insert the new assignment's month deadline >>> ")
        deadline_day = input("Insert the new assignment's day deadline >>> ")
        try:
            deadline = datetime.datetime(int(deadline_year) , int(deadline_month) , int(deadline_day))
        except:
            raise ValueError("Deadline format should be YYYY - MM - DD!")
        self.__assignment_service.add_assignment(assignmentID , description , deadline)
        print("Assignment added succesfully!")
        self.__undoredo.undo_operation(self.__assignment_service.remove_assignment , assignmentID , description , deadline)

    def ui_remove_assignment(self):

        assignmentID = int(input("Insert the assignment's ID that you wish to remove >>> "))

        removed_id, removed_description, removed_deadline = self.__assignment_service.remove_assignment(assignmentID, None, None)
        print("Assignment removed succesfully!")
        self.__undoredo.undo_operation(self.__assignment_service.add_assignment , removed_id , removed_description , removed_deadline)

    def ui_update_assignment(self):

        assignmentID = int(input("Insert the assignment's ID that you wish to update >>> "))
        update = input("Insert the new description for the assignment >>> ")

        old_description = self.__assignment_service.update_assignment(assignmentID , update, None)
        print("Assignment updated succesfully!")
        self.__undoredo.undo_operation(self.__assignment_service.update_assignment , assignmentID , old_description , update)

    def ui_list_assignments(self):

        assignments = self.__assignment_service.get_all_assignments()
        for assignment in assignments:
            print(str(assignment))

    def ui_give_assignment_student(self):

        studentID = int(input("Insert the student's ID that you want to give the assignment to >>> "))
        assignmentID = int(input("Insert the assignment's ID >>> "))
        self.__grade_service.give_assignment(studentID , assignmentID , 0)
        print("Homework assigned succesfully!")
        self.__undoredo.undo_operation(self.__grade_service.remove_assignment_given , studentID, assignmentID, 0)

    def ui_give_assignment_group(self):

        groupID = int(input("Insert the group's ID that you want to give the assignment to >>> "))
        assignmentID = int(input("Insert the assignment's ID >>> "))
        students = self.__student_service.get_group_students(groupID)
        for studentID in students:
            self.__grade_service.give_assignment(studentID , assignmentID , 0)
            self.__undoredo.undo_operation(self.__grade_service.remove_assignment_given, studentID, assignmentID, 0)
        print("Homework assigned succesfully!")

    def ui_give_grade(self):

        studentID = int(input("Insert the student's ID that you want to give a grade to >>> "))
        assignmentID = int(input("Insert the assignment's ID that you want to grade >>> "))
        grade = int(input("Insert the grade >>> "))
        self.__grade_service.give_grade(studentID , assignmentID , grade)
        print("Grade given succesfully!")

    def ui_students_with_assignment(self):

        assignmentID = int(input("Insert the assignment's ID that you want to check >>> "))
        grades = self.__grade_service.students_with_assignment(assignmentID)
        for grade in grades:
            print(str(grade))

    def ui_late_students(self):

        print(self.__grade_service.late_students())

    def ui_best_students(self):

        print(self.__grade_service.best_students())

    def ui_undo(self):
        if self.__undoredo.undos_left() == 0:
            print("Nothing to undo!")
        else:
            self.__undoredo.undo()

    def ui_redo(self):
        if self.__undoredo.redos_left() == 0:
            print("Nothing to redo!")
        else:
            self.__undoredo.redo()


    def menu(self):

        print("1. Manage students.")
        print("2. Manage assigments.")
        print("3. Give a grade.")
        print("4. All students who received a given assignment, ordered by average grade for that assignment.")
        print("5. All students who are late in handing in at least one assignment.")
        print("6. Students with the best school situation.")
        print("7. Undo last operation.")
        print("8. Redo last operation.")

    def user_input(self):

        user_choice = int(input("\nSelect option >>> "))
        commands = {1: self.manage_students , 2: self.manage_assignments , 3: self.ui_give_grade ,
                    4: self.ui_students_with_assignment , 5: self.ui_late_students , 6: self.ui_best_students, 7:self.ui_undo, 8:self.ui_redo}
        commands[user_choice]()

    def generated_data(self):

        self.__student_service.add_student(10 , "Student Test" , 10)
        self.__student_service.add_student(11 , "Test Student" , 10)
        self.__assignment_service.add_assignment(10 , "Assignment Test" , datetime.datetime(2000 , 5 , 11))
        self.__assignment_service.add_assignment(11 , "Test Assignment" , datetime.datetime(2020 , 5 , 11))
        self.__grade_service.give_assignment(10, 10, 0)
        self.__grade_service.give_grade(10, 10, 5)
        self.__grade_service.give_assignment(11 , 10 , 0)
        self.__grade_service.give_grade(11 , 10 , 10)
        self.__student_service.generate_students()
        self.__assignment_service.generate_assignments()

    def run(self):
        self.menu()
        while True:
            try:
                self.user_input()
            except ValueError as error:
                print(error)
            except RepoError as error:
                print(error)
            except ValidError as error:
                print(error)
