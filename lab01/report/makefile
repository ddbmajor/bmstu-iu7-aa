main.pdf: main.tex
	xelatex --shell-escape $^
	make rpdf
	xelatex --shell-escape $^


.PHONY: clean rpdf

clean:
	rm *.aux *.log *.out *.toc *.xdv

rpdf:
	rm *.pdf
