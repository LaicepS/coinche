def Settings( **kwargs ):
    return {
    'flags': [ '-x', 'c++', '-Wall', '-Werror', '-std=c++2a', '-Werror=missing-field-initializers'
        , '-I', '.'
        ],
    }
