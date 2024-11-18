vars = {}
while a:=input():
    try:
        if not a:
            break
        if a.startswith("#"):
            continue
        if "=" in a:
            ids, e = a.split("=", 1)
            ids = ids.strip()
            e = e.strip()
            if not ids.isidentifier():
                print("Assignment error")
                continue
            try:
                value = eval(e, {'__builtins__': {}}, vars)
                vars[ids] = value
            except SyntaxError:
                print("Syntax error")
            except NameError:
                print("Name error")
            except:
                print("Runtime error")
        else:
            try:
                result = eval(a,  {'__builtins__': {}}, vars)
                print(result)
            except SyntaxError:
                print("Syntax error")
            except NameError:
                print("Name error")
            except:
                print("Runtime error")
    except EOFError:
        break