import unittest
from domain import Student , Assignment, Grade
from repository import Repository
from exceptions import RepoError

class StudentTests(unittest.TestCase):

    def setUp(self):
        self.__student_repository = Repository()
        self.__student_repository.add(Student(1, "Test Student", 917))
        self.__student_repository.add(Student(2, "Student Test", 916))
        self.addValidInput = Student(3, "Le Student", 916)
        self.addInvalidInput = Student(1, "Le Student", "da")
        self.removeValidInput = Student(1, None, None)
        self.removeInvalidInput = Student(5, None, None)
        self.updateValidInput = Student(1, None, None)
        self.updateInvalidInput = Student(5, None, None)
        self.updateParameter = "New Student"

    def test__add_student__validInput__addsStudent(self):
        self.__student_repository.add(self.addValidInput)
        students = self.__student_repository.get_all_items()
        self.assertEqual(students, [Student(1, "Test Student", 917), Student(2, "Student Test", 916), Student(3, "Le Student", 916)])

    def test__add_student__invalidInput__raisesError(self):
        try:
            self.__student_repository.add(self.addInvalidInput)
        except RepoError:
            pass
        self.assertRaises(RepoError)

    def test__remove_student__validInput__removesStudent(self):
        self.__student_repository.remove(self.removeValidInput)
        students = self.__student_repository.get_all_items()
        self.assertEqual(students, [Student(2, "Student Test", 916)])

    def test__remove_student__invalidInput__raisesError(self):
        try:
            self.__student_repository.remove(self.removeInvalidInput)
        except RepoError:
            pass
        self.assertRaises(RepoError)

class AssignmentTests(unittest.TestCase):

    def setUp(self):
        self.__assignment_repository = Repository()
        self.__assignment_repository.add(Assignment(1 , "Test Assignment" , 917))
        self.__assignment_repository.add(Assignment(2 , "Assignment Test" , 916))
        self.addValidInput = Assignment(3 , "Le Assignment" , 916)
        self.addInvalidInput = Assignment(1 , "Le Assignment" , "da")
        self.removeValidInput = Assignment(1 , None , None)
        self.removeInvalidInput = Assignment(5 , None , None)
        self.updateValidInput = Assignment(1 , None , None)
        self.updateInvalidInput = Assignment(5 , None , None)
        self.updateParameter = "New Assignment"

    def test__add_assignment__validInput__addsAssignment(self):
        self.__assignment_repository.add(self.addValidInput)
        assignments = self.__assignment_repository.get_all_items()
        self.assertEqual(assignments , [Assignment(1 , "Test Assignment" , 917) , Assignment(2 , "Assignment Test" , 916) ,
                                     Assignment(3 , "Le Assignment" , 916)])

    def test__add_assignment__invalidInput__raisesError(self):
        try:
            self.__assignment_repository.add(self.addInvalidInput)
        except RepoError:
            pass
        self.assertRaises(RepoError)

    def test__remove_assignment__validInput__removesAssignment(self):
        self.__assignment_repository.remove(self.removeValidInput)
        assignments = self.__assignment_repository.get_all_items()
        self.assertEqual(assignments , [Assignment(2 , "Assignment Test" , 916)])

    def test__remove_assignment__invalidInput__raisesError(self):
        try:
            self.__assignment_repository.remove(self.removeInvalidInput)
        except RepoError:
            pass
        self.assertRaises(RepoError)