class morse:
    def __init__(self, params = "di dit dah"):
        self.word_mode = " " in params
        if " " in params:
            parts = params.split()
            if len(parts) == 2:
                self.dot, self.dash = parts
                self.end_dot = self.dot
                self.end_msg = ""
            elif len(parts) == 3:
                if params[-1] != ' ':
                    self.dot, self.end_dot, self.dash = parts
                    self.end_msg = "."
                else:
                    self.dot, self.end_dot, self.dash = parts
                    self.end_msg = " "
            elif len(parts) == 4:
                self.dot, self.end_dot, self.dash, self.end_msg = parts
        elif params == "":
            self.dot, self.end_dot, self.dash = "di", "dit", "dah"
            self.end_msg = "."
        else:
            if len(params) == 2:
                self.dot, self.dash = params
                self.end_dot = self.dot
                self.end_msg = ""
            elif len(params) == 3:
                self.dot, self.end_dot, self.dash = params
                self.end_msg = ""
            elif len(params) == 4:
                self.dot, self.end_dot, self.dash, self.end_msg = params
        self.expression = "!"

    def __pos__(self):
        self.expression += "+"
        return self

    def __neg__(self):
        self.expression += "-"
        return self

    def __invert__(self):
        self.expression += "~"
        return self

    def _convert_symbol(self, symbol):
        if symbol == '+':
            return self.dot
        elif symbol == '-':
            return self.dash
        elif symbol == '*':
            return self.end_dot
        elif symbol == '~':
            return ", " if self.word_mode else " "
        return ""

    def _translate_expression(self):
        morse_code = ""
        if self.word_mode:
            s = self.expression.replace('~+', '~*')
            s = s.replace('!+', '*')
            for char in s:
                morse_code = self._convert_symbol(char) + morse_code
            result = morse_code
            result = result.replace(self.dot, f" {self.dot}").replace(self.end_dot, f" {self.end_dot}").replace(
                self.dash, f" {self.dash}")
            result = result.strip().replace(",  ", ", ").replace("  ", " ")
            return result + self.end_msg
        s = self.expression.replace('~+', '~*')
        s = s.replace('!+', '*')
        for char in s:
            morse_code = self._convert_symbol(char) + morse_code
        result = morse_code
        return result + self.end_msg

    def __str__(self):
        return self._translate_expression()
