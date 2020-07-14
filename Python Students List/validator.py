from exceptions import ValidError

class StudentValidator():

    def validate_student(self, student):
        errors = ""

        if int(student.get_id()) < 0:
            errors += "Invalid student ID! Must be an integer.\n"
        if student.get_name() == "":
            errors += "Invalid name! It can't be empty!\n"
        if int(student.get_group()) < 0:
            errors += "Invalid group! Must be an integer.\n"


        if len(errors) > 0:
            raise ValidError(errors)

class AssignmentValidator():

    def validate_assignment(self , assignment):
        errors = ""

        if int(assignment.get_id()) < 0:
            errors += "Invalid assignment ID! Must be an integer.\n"
        if assignment.get_description() == "":
            errors += "Invalid description! It can't be empty!\n"

        if len(errors) > 0:
            raise ValidError(errors)

class GradeValidator():

    def validate_grade(self , grade , student_true , discipline_true):
        errors = ""

        if (grade.get_grade() < 0):
            errors += "The grade can't be negative!"
        if (grade.get_grade() > 10):
            errors += "The grade can't be greater than 10!"
        if student_true == False:
            errors += "The grade can't be given to an inexisting student!"
        if discipline_true == False:
            errors += "The grade can't be given to an inexisting discipline!"

        if len(errors) > 0:
            raise ValidError(errors)