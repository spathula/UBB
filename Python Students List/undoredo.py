class UndoRedo:
    def __init__(self, student_service, assignment_service, grade_service):
        self.__student_service = student_service
        self.__assignment_service = assignment_service
        self.__grade_service = grade_service
        self.__undo_operations = []
        self.__redo_operations = []
        self.__call_operations = {'add_student':self.__student_service.remove_student,
                                     'remove_student':self.__student_service.add_student,
                                     'update_student':self.__student_service.update_student,
                                  'add_assignment':self.__assignment_service.remove_assignment,
                                  'remove_assignment':self.__assignment_service.add_assignment,
                                  'update_assignment':self.__assignment_service.update_assignment,
                                  'give_assignment':self.__grade_service.remove_assignment_given,
                                  'give_grade':self.__grade_service.remove_grade,
                                  'remove_assignment_given':self.__grade_service.give_assignment,
                                  'remove_grade':self.__grade_service.give_grade}

    def undos_left(self):
        return len(self.__undo_operations)

    def redos_left(self):
        return len(self.__redo_operations)

    def undo_operation(self, operation, parameter1, parameter2, parameter3):
        undo_operation = []
        undo_operation.append(operation)
        undo_operation.append(parameter1)
        undo_operation.append(parameter2)
        undo_operation.append(parameter3)
        self.__undo_operations.append(undo_operation)

    def undo(self):
        self.__undo_operations[-1][0](self.__undo_operations[-1][1] , self.__undo_operations[-1][2] , self.__undo_operations[-1][3])
        if self.__undo_operations[-1][0] == self.__student_service.update_student or self.__undo_operations[-1][0] == self.__assignment_service.update_assignment:
            parameter2 = self.__undo_operations[-1][3]
            parameter3 = self.__undo_operations[-1][2]
        else:
            parameter2 = self.__undo_operations[-1][2]
            parameter3 = self.__undo_operations[-1][3]
        parameter1 = self.__undo_operations[-1][1]
        operation = self.__call_operations[self.__undo_operations.pop()[0].__name__]
        redo_operation = []
        redo_operation.append(operation)
        redo_operation.append(parameter1)
        redo_operation.append(parameter2)
        redo_operation.append(parameter3)
        self.__redo_operations.append(redo_operation)

    def redo(self):
        self.__redo_operations[-1][0](self.__redo_operations[-1][1] , self.__redo_operations[-1][2] , self.__redo_operations[-1][3])
        if self.__redo_operations[-1][0] == self.__student_service.update_student or self.__redo_operations[-1][0] == self.__assignment_service.update_assignment:
            parameter2 = self.__redo_operations[-1][3]
            parameter3 = self.__redo_operations[-1][2]
        else:
            parameter2 = self.__redo_operations[-1][2]
            parameter3 = self.__redo_operations[-1][3]
        parameter1 = self.__redo_operations[-1][1]
        operation = self.__call_operations[self.__redo_operations.pop()[0].__name__]
        undo_operation = []
        undo_operation.append(operation)
        undo_operation.append(parameter1)
        undo_operation.append(parameter2)
        undo_operation.append(parameter3)
        self.__undo_operations.append(undo_operation)
