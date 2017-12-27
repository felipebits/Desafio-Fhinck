# Desafio Fhinck
Pré-requisitos: C++, PHP, Infraestrutura de TI, APIs Windows, Javascript.

Diferencial: Kubernetes, Google BigQuery e Microsoft Azure.

"A Fhinck está em busca de um engenheiro de software

O desejado profissional deverá ter habilidades diferenciadas, tais como o raciocínio analítico apurado, a visão holística do sistema e a onisciência … sim, você precisará saber de tudo que está acontecendo a todo tempo. A clarividência será considerada um diferencial.

Por se tratar de um ambiente único e com tecnologias de ponta, o profissional deverá minimamente ter experiência como arquiteto e desenvolvedor de software ou infraestrutura para sistemas escaláveis e distribuídos, além de ter conhecimento em tecnologias tais como Big Data e SaaS. Além de desenvolver nossa plataforma, você deverá ser capaz de imaginar, prototipar, criar e suportar novamente todas as loucuras que forem desenvolvidas em nosso starmap (roadmap é para os fracos...). Pensar fora da caixa é o mínimo esperado, isso está profundamente enraizado no DNA de todo Fhincker!

Além de executar, analisar, criar e surpreender, o desenvolvedor da Fhinck tem que ser também extremamente organizado, já que toda documentação servirá de legado de lições aprendidas ao longo do caminho. Por falar em caminho, nunca se sabe onde poderemos estar no dia seguinte, portanto tenha seu passaporte e visto USA atualizados e seja fluente em inglês ... or use the force when it gets to it, that’s your call.

Completam o perfil o exercício diário de aprendizado em disciplinas diversas, tais como: orador (você dará pitchs diariamente, ou a todo momento a depender do movimento no Cubo), orgulho nerd (sim, somos nerds e conversamos sobre tudo que você imagina, então se deseja impressionar venha vestido de Vader ou Leia Organa), dançarino (às vezes, quando estamos de frente pro cliente, as coisas podem não funcionar muito bem, portanto já sabe ... traga os sapatos de dança e entretenha nosso cliente) e vendedor ... sim, todos nós somos vendedores 24 por 7 e conhecemos as necessidades de nossos clientes melhor do que os próprios, caso não esteja preparado pra isso pense duas vezes antes de escolher a pílula vermelha. E se você não entendeu esta última referência nem ouse se inscrever!!!!!"

Desafio

Arquivos secretos do império foram roubados, e o Grande Almirante Thrawn decide fazer uma auditoria em todos os terminais de sua nave, suspeitando que os arquivos foram enviados por um agente duplo. Com isso, ele pede sua ajuda para criar um sistema de monitoramento, que irá capturar toda vez que o soldado do império bloquear seu terminal. O sistema operacional das máquinas é Windows 10.

Quando o terminal for desbloqueado, o sistema deve mostrar uma janela perguntando ao soldado o motivo de sua saída do terminal.

As opções de resposta são: - Patrulhamento

- Almoço no refeitório

- Escolta de prisioneiro

Caso o soldado responda “Patrulhamento”, o sistema deverá permitir um detalhamento da opção através de um campo texto.

Depois de completada a tela de entrada do motivo de bloqueio, o sistema deverá armazenar no banco de dados do império (qual o BD fica a seu critério) o nome de usuário do soldado, além de qual opção foi selecionada.

Caso o usuário não responda o alerta em 15 segundos, o sistema deverá utilizar a webcam do terminal, tirar uma foto do soldado e enviar para o banco de dados como blob junto com as demais informações acima, caso o terminal não possua webcam, uma cópia da tela da estação de trabalho deve ser capturada e armazenada no blob.

Use a linguagem C++ para criar esta solução para o Império.