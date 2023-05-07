#tester function
def email_test(email):
    alphabets = 'abcdefghijklmnopqrstuvwxyz'
    numbers = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    state = 's1'
    i = 0
    while i<len(email):
        if state == 's1':
            if email[i] in alphabets:
                state = 's2'
            elif email[i] in numbers:
                state = 's3'
            elif email[i] == '.':
                state = 's4'
            elif email[i] == '@':
                state = 's5'
            else:
                state = 'error'
        elif state == 's2':
            if email[i] in alphabets:
                state = 's2'
            elif email[i] in numbers:
                state = 's3'
            elif email[i] == '.':
                state = 's4'
            elif email[i] == '@':
                state = 's5'
            else:
                state = 'error'
        elif state == 's3':
            if email[i] in alphabets:
                state = 's2'
            elif email[i] in numbers:
                state = 's3'
            elif email[i] == '.':
                state = 's4'
            elif email[i] == '@':
                state = 's5'
            else:
                state = 'error'
        elif state == 's4':
            if email[i] in alphabets:
                state = 's2'
            elif email[i] in numbers:
                state = 's3'
            elif email[i] == '.':
                state = 's4'
            elif email[i] == '@':
                state = 's5'
            else:
                state = 'error'
        elif state == 's5':
            if email[i] in alphabets:
                state = 's6'
            elif email[i] in numbers:
                state = 's7'
            elif email[i] == '.':
                state = 's10'
            else:
                state = 'error'
        elif state == 's6':
            if email[i] in alphabets:
                state = 's6'
            elif email[i] in numbers:
                state = 's7'
            elif email[i] == '.':
                state = 's9'
            else:
                state = 'error'
        elif state == 's7':
            if email[i] in alphabets:
                state = 's6'
            elif email[i] in numbers:
                state = 's7'
            elif email[i] == '.':
                state = 's9'
            else:
                state = 'error'
        elif state == 's8':
            if email[i] in alphabets:
                state = 's6'
            elif email[i] in numbers:
                state = 's7'
            elif email[i] == '.':
                state = 's9'
            else:
                state = 'error'
        elif state == 's9':
            if email[i] in alphabets:
                state = 's10'
            elif email[i] in numbers:
                state = 's7'
            elif email[i] == '.':
                state = 's9'
        elif state == 's10':
            if email[i] in alphabets:
                state = 's10'
            elif email[i] == '.':
                state = 's9'
            else:
                state = 'error'
        if state == 'error':
            break
        i+=1

    return state

if __name__=='__main__':
    test_emails = ['teszt@sze.hu','@','@.','', '@@@@@.', 'teszt', 'teszt.elek@valid.email.hu', 'teszt@@@@@..teszt.hu', '.', 'teszt@']
    
    print('Tester')
    
    for index, case in enumerate(test_emails, start=1):
        print('------------')
        print(f'Case {index}')
        print (f'|{case}| case test:')
        result= email_test(case)
        if result == 'error':
            print('Failed test')
        else:
            print('Passed test')
        print('------------')
        
        
    
    