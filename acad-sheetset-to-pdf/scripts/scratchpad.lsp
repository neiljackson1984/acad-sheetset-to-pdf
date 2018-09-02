(vlax-for plotConfiguration (vla-get-PlotConfigurations (vla-get-ActiveDocument (vlax-get-acad-object)))
	(princ "found a plotConfiguration: ")(princ (vla-get-Name plotConfiguration))(princ "\n")
)
(princ)
