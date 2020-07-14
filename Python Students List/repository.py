from exceptions import RepoError
import pickle
class Repository():

    def __init__(self):
        self._items = []

    def size(self):
        return len(self._items)

    def add(self, item):
        if item in self._items:
            raise RepoError("The item you are trying to add already exists!")
        self._items.append(item)

    def search(self, item):
        if item not in self._items:
            raise RepoError("The item you are searching doesn't exist!")
        for item_required in self._items:
            if item_required == item:
                return item_required

    def check_existence(self , item):
        if item not in self._items:
            return False
        return True

    def remove(self, item):
        item = self.search(item)
        if item not in self._items:
            raise RepoError("The item you are trying to delete doesn't exist!")
        self._items.remove(item)

    def get_all_items(self):
        if len(self._items) == 0:
            raise RepoError("The list is empty!")
        return self._items[:]

    def get_all_grades_student(self , id):
        required_list = []
        for item in self._items:
            if item.get_studentID() == id:
                required_list.append(item)
        return required_list[:]

    def get_all_grades_assignment(self , id):
        required_list = []
        for item in self._items:
            if item.get_assignmentID() == id:
                required_list.append(item)
        return required_list[:]

class FileRepository(Repository):

    def __init__(self, filename, read_entity, write_entity):
        Repository.__init__(self)
        self.__filename = filename
        self.__read_entity = read_entity
        self.__write_entity = write_entity

    def __read_all_from_file(self):
        self._items = []
        with open(self.__filename , "r") as file:
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    item = self.__read_entity(line)
                    self._items.append(item)

    def __write_all_to_file(self):
        with open(self.__filename , "w") as file:
            for item in self._items:
                line = self.__write_entity(item)
                file.write(line + "\n")
            file.close()

    def add(self , item):
        self.__read_all_from_file()
        Repository.add(self , item)
        self.__write_all_to_file()

    def search(self , item):
        self.__read_all_from_file()
        return Repository.search(self , item)

    def check_existence(self , item):
        self.__read_all_from_file()
        return Repository.check_existence(self , item)

    def remove(self, item):
        self.__read_all_from_file()
        Repository.remove(self, item)
        self.__write_all_to_file()

    def get_all_items(self):
        self.__read_all_from_file()
        return Repository.get_all_items(self)

    def get_all_grades_student(self , id):
        self.__read_all_from_file()
        return Repository.get_all_grades_student(self, id)

    def get_all_grades_assignment(self , id):
        self.__read_all_from_file()
        return Repository.get_all_grades_assignment(self, id)

class PickleRepository(Repository):

    def __init__(self, filename, read_entity, write_entity):
        Repository.__init__(self)
        self.__filename = filename
        self.__read_entity = read_entity
        self.__write_entity = write_entity

    def __read_all_from_file(self):
        self._items = []
        self.lines = []
        with open(self.__filename , "rb") as file:
            while True:
                try:
                    lines = pickle.load(file)
                except EOFError:
                    break
                lines = lines.split(",")
                self.lines.append(lines)
            for line in self.lines:
                item = self.__read_entity(line)
                self._items.append(item)

    def __write_all_to_file(self):
        with open(self.__filename , "wb") as file:
            for item in self._items:
                line = self.__write_entity(item)
                pickle.dump(line , file)
            file.close()

    def add(self , item):
        self.__read_all_from_file()
        Repository.add(self , item)
        self.__write_all_to_file()

    def search(self , item):
        self.__read_all_from_file()
        return Repository.search(self , item)

    def check_existence(self , item):
        self.__read_all_from_file()
        return Repository.check_existence(self , item)

    def remove(self, item):
        self.__read_all_from_file()
        Repository.remove(self, item)
        self.__write_all_to_file()

    def get_all_items(self):
        self.__read_all_from_file()
        return Repository.get_all_items(self)

    def get_all_grades_student(self , id):
        self.__read_all_from_file()
        return Repository.get_all_grades_student(self, id)

    def get_all_grades_assignment(self , id):
        self.__read_all_from_file()
        return Repository.get_all_grades_assignment(self, id)