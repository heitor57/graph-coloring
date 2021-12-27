(TeX-add-style-hook
 "doc"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("article" "11pt")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("fontenc" "T1") ("ulem" "normalem") ("babel" "portuguese") ("siunitx" "binary-units=true") ("geometry" "top=0.5cm" "bottom=1.5cm" "left=2cm" "right=2cm") ("algpseudocode" "noend") ("caption" "font=small" "labelfont=bf") ("subcaption" "subrefformat=parens")))
   (add-to-list 'LaTeX-verbatim-environments-local "lstlisting")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "lstinline")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "lstinline")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art11"
    "inputenc"
    "fontenc"
    "graphicx"
    "grffile"
    "longtable"
    "wrapfig"
    "rotating"
    "ulem"
    "amsmath"
    "textcomp"
    "amssymb"
    "capt-of"
    "hyperref"
    "babel"
    "mathtools"
    "siunitx"
    "geometry"
    "mdframed"
    "listings"
    "algpseudocode"
    "algorithm"
    "tikz"
    "caption"
    "subcaption")
   (TeX-add-symbols
    '("algrule" ["argument"] 0)
    '("algstrut" ["argument"] 0)
    '("Let" 2)
    "algruledefaultfactor"
    "Stateh"
    "myDistance")
   (LaTeX-add-labels
    "sec:orgb5453dc"
    "sec:orge276677"
    "sec:orgffd25b9"
    "sec:org6df95d0"
    "alg:coloringBranchnBound"
    "alg:coloringBranchnBoundR"
    "alg:coloringBranchnBoundR:for1"
    "alg:coloringBranchnBoundR:adjnotsamecolor"
    "alg:coloringBranchnBoundR:color"
    "alg:coloringBranchnBoundR:last"
    "sec:org8084315"
    "alg:coloringDSatur"
    "alg:coloringDSatur:while"
    "sec:org93a5342"
    "alg:coloringRLF"
    "sec:org775dfdc"
    "sec:orge0976fa"
    "sec:org3466444"
    "sec:orgad97ba9"
    "sec:org6781124"
    "sec:org402a2d7"
    "sec:org68f5cc8"
    "sec:org3adde23"
    "sec:orgbde5ada"
    "sec:org79611b0"
    "tab:org8070bd0"
    "sec:org484d0a2"
    "sec:orgf451f53"
    "fig:vertice-aresta-a"
    "fig:vertice-aresta-b"
    "fig:vertice-aresta"
    "sec:orga493adc")
   (LaTeX-add-bibliographies))
 :latex)

