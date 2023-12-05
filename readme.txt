===========================================================================================================
                         INSTRUÇÕES PARA COMPILAÇÃO E EXECUÇÃO
===========================================================================================================

**Compilação do Gerador:**
   - Comando: `gcc -o Gerador gerador.c Lista.o`
   - Execução: `./Gerador dados.txt dadosBIN.bin`
   - Formato dos dados: "id nome"
   - Exemplo: `17 moriel_silva`

**Compilação do Editor:**
   - Comando: `gcc -o Editor editor.c Lista.o`
   - Execução: `./Editor dadosBIN.bin dadosEDITADOS.bin`

**Compilação do Exportador:**
   - Comando: `gcc -o Exportador exportador.c Lista.o`
   - Execução: `./exportador dadosEDITADOS.bin dadosFINAIS.txt`

===========================================================================================================
                          README - INFORMAÇÕES IMPORTANTES
===========================================================================================================

Este é um conjunto de programas que realiza operações em dados binários:

- O programa "Gerador" compila dados de entrada (formato: id nome) em um arquivo binário.
- O programa "Editor" edita dados binários existentes e cria um novo arquivo binário.
- O programa "Exportador" converte dados binários editados em um arquivo de texto final.

===========================================================================================================
