{
  'target_defaults': {
    'conditions': [
      ['OS=="win"', {
        'defines': [
          '_WIN32_WINNT=0x0600',
        ],
      }],
    ],
    'msbuild_settings': {
      'ClCompile': {
        'WarningLevel': 'Level3',
        'Optimization': 'Full',
        'FunctionLevelLinking': 'true',
      },
      'Lib': {
        'LinkTimeCodeGeneration': 'true',
      },
    },
    'msvs_settings': {
      'VCCLCompilerTool': {
        'WarningLevel': '3',
        'Optimization': '3',
        'EnableFunctionLevelLinking': 'true',
      },
      'VCLibrarianTool': {
        'LinkTimeCodeGeneration': 'true',
      },
    },
    'xcode_settings': {
      'CLANG_CXX_LANGUAGE_STANDARD': 'c++11',
      'CLANG_CXX_LIBRARY': 'libc++',
      'CLANG_ENABLE_OBJC_ARC': 'YES',
      'GCC_OPTIMIZATION_LEVEL': '3',
      'GCC_VERSION': 'com.apple.compilers.llvm.clang.1_0',
      'GCC_WARN_SHADOW': 'YES',
      'GCC_WARN_UNUSED_VARIABLE': 'YES',
      'WARNING_CFLAGS': ['-Wall'],
    },
  },
  'targets': [
    {
      'target_name': 'addon',
      'include_dirs': [
        '<!(node -e "require(\'nan\')")',
      ],
      'sources': [
        'addon.cpp',
      ],
      'conditions': [
        ['OS=="mac"', {
          'link_settings': {
            'libraries': [
              '-framework AppKit',
            ],
          },
          'sources': [
            'system_icon_mac.mm',
          ],
        }],
        ['OS=="win"', {
          'link_settings': {
            'libraries': [
              'Gdiplus.lib',
            ],
          },
          'sources': [
            'system_icon_win.cpp',
          ],
        }],
        ['OS!="mac" and OS!="win"', {
          'sources': [
            'system_icon.cpp',
          ],
        }],
      ],
    },
  ],
}
