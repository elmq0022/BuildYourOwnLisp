def Settings(**kwargs):
    return{
        'flags':[
            '-x',
            'c',
            '-Wall',
            '-std=c99',
            '-lreadline',
            '-lm',
        ],
    }
