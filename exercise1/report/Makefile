.PHONY: clean
FILE=group_13_exercise_1_report

all: $(FILE).pdf

$(FILE).pdf: $(FILE).tex
	pdflatex $(FILE)
	bibtex $(FILE)
	pdflatex $(FILE)

clean:
	rm -rf *.aux *.bbl *.blg *.dvi *.log *.out *.synctex.gz *.toc *.lot *.lof
