def Settings(**kwargs):
    return{
            'flags': [
                '-x',
                'c',
                '-std=c99',
                '-Wall',
                '-lreadline',
                '-lm',
            ]
    }
