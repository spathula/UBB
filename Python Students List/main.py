from repository import Repository, FileRepository, PickleRepository
from validator import StudentValidator, AssignmentValidator, GradeValidator
from service import StudentService, AssignmentService, GradeService
from domain import Student, Assignment, Grade
from interface import Interface
from undoredo import UndoRedo

settings = open('settings.properties' , 'r')
repository_type = settings.readlines()
settings.close()

if repository_type[0] == 'memory':
    student_repository = Repository()
    assignment_repository = Repository()
    grade_repository = Repository()
elif repository_type[0] == 'file':
    student_repository = FileRepository("students.txt", Student.read_student, Student.write_student)
    assignment_repository = FileRepository("assignments.txt", Assignment.read_assignment, Assignment.write_assignment)
    grade_repository = FileRepository("grades.txt", Grade.read_grade, Grade.write_grade)
elif repository_type[0] == 'binary':
    student_repository = PickleRepository("students.pickle", Student.read_student_pickle, Student.write_student)
    assignment_repository = PickleRepository("assignments.pickle", Assignment.read_assignment_pickle, Assignment.write_assignment)
    grade_repository = PickleRepository("grades.pickle", Grade.read_grade_pickle, Grade.write_grade)

student_validator = StudentValidator()
assignment_validator = AssignmentValidator()
grade_validator = GradeValidator()

student_service = StudentService(student_repository, student_validator, grade_repository)
assignment_service = AssignmentService(assignment_repository, assignment_validator, grade_repository)
grade_service = GradeService(grade_repository, grade_validator, student_repository, assignment_repository)

undoredo = UndoRedo(student_service, assignment_service, grade_service)

interface = Interface(student_service, assignment_service, grade_service, undoredo)

interface.run()