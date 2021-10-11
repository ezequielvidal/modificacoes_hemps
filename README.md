# modificacoes_HeMPS
Este repositório detalha implementações na plataforma MPSoC HeMPS para aceitar novas heurísticas de mapeamento de tarefas.

Por: Ezequiel Vidal - contato: ezequielvidal.ti@gmail.com

INFORMACOES REFERENTES ÀS MODIFICACOES REALIZADAS NA HEMPS

*Todos os codigos estão na pasta compactada "hemps_novas_implementacoes.zip" deste repositorio.

*O arquivo heuristicas.c traz apenas uma demostração dos codigos das heuristicas, implementados na hemps.

*Os arquivos links.h e links.c trazem a implementacao dos links de comunicação, adicionados na hemps.

*Pequenas modificações tiveram que ser realizados no arquivo app_builder.py em (hemps/hemps8.5/build_env/scripts/app_builder.py),para que o grafo das aplicações fosse lido pela plataforma.

*O arquivo do grafo de aplicação também sofreu pequenas alterações. Os grafos ficam na própria pasta de cada aplicação, como em
(hemps/hemps8.5/applications/dtw/dtw.cfg).

*A plataforma HeMPS original se encontra no endereço https://www.inf.pucrs.br/hemps/
