target_sources(Disassembler-test PRIVATE
        generators/concatinate.cpp
        generators/not_in.cpp
        generators/resettable.cpp
        generators/x86Environment.cpp
        generators/prefixList.cpp
        endian.cpp
        imm.cpp
        )