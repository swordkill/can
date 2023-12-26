#: MIT License
#
#: Copyright (c) 2023 Saï 才 <git@onyle.com>
#
#: Permission is hereby granted, free of charge, to any person obtaining a copy
#: of this software and associated documentation files (the "Software"), to deal
#: in the Software without restriction, including without limitation the rights
#: to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#: copies of the Software, and to permit persons to whom the Software is
#: furnished to do so, subject to the following conditions:
#
#: The above copyright notice and this permission notice shall be included in
#: all copies or substantial portions of the Software.
#
#: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#: IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#: FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#: AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#: LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#: OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#: SOFTWARE.

CC := gcc

SRL := demo/generic_list.c
SRA := demo/variable_array.c
EXL := program_can_list
EXA := program_can_vla

.RECIPEPREFIX := >
.PHONY        := list vla clean

exe :
> $(CC) -I. -o $(EXL) $(SRL)
> $(CC) -I. -o $(EXA) $(SRA)

all :| clean exe;

list :
> $(if $(wildcard $(EXL)),$(info ...executing $(EXL))@./$(EXL))

vla :
> $(if $(wildcard $(EXA)),$(info ...executing $(EXA))@./$(EXA))

clean :
> $(if $(wildcard $(EXL)),$(info ...removing  $(EXL))@rm -f $(EXL))
> $(if $(wildcard $(EXA)),$(info ...removing  $(EXA))@rm -f $(EXA))
