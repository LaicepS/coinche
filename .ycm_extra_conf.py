def Settings( **kwargs ):
    return {
    'flags': [ '-x', 'c++', '-Wall', '-Werror', '-std=c++17', '-Werror=missing-field-initializers'
        , '-I', '.'
        ],
    }
