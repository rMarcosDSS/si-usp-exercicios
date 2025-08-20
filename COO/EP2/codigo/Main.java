import java.io.IOException;
import java.util.Comparator;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Uso:");
            System.out.println("\tjava " + Main.class.getName() + " <arquivo CSV> <algoritmo> <critério de ordenação> [<critério de filtragem> <parâmetro de filtragem>]");
            System.out.println("Onde:");
            System.out.println("\tarquivo CSV: caminho para o arquivo CSV contendo os produtos");
            System.out.println("\talgoritmo: 'quick' ou 'insertion'");
            System.out.println("\tcriterio de ordenação: 'preco_c' ou 'descricao_c' ou 'estoque_c' ou 'preco_d' ou 'descricao_d' ou 'estoque_d'");
            System.out.println("\tcriterio de filtragem (opcional): 'todos' ou 'estoque_menor_igual' ou 'categoria_igual' ou 'preco_intervalo' ou 'descricao_contem'");
            System.out.println("\tparâmetro de filtragem (opcional): argumentos adicionais necessários para a filtragem");
            System.out.println();
            System.exit(1);
        }

        String caminhoArquivoCSV = args[0];
        String opcao_algoritmo = args[1];
        String opcao_criterio_ord = args[2];
        String opcao_criterio_filtro = args.length > 3 ? args[3] : "todos";
        String opcao_parametro_filtro = args.length > 4 ? args[4] : "";

        Comparator<Produto> comparator;
        switch (opcao_criterio_ord) {
            case "descricao_c":
                comparator = Comparator.comparing(Produto::getDescricao);
                break;
            case "preco_c":
                comparator = Comparator.comparingDouble(Produto::getPreco);
                break;
            case "estoque_c":
                comparator = Comparator.comparingInt(Produto::getQtdEstoque);
                break;
            case "descricao_d":
                comparator = Comparator.comparing(Produto::getDescricao).reversed();
                break;
            case "preco_d":
                comparator = Comparator.comparingDouble(Produto::getPreco).reversed();
                break;
            case "estoque_d":
                comparator = Comparator.comparingInt(Produto::getQtdEstoque).reversed();
                break;
            default:
                throw new IllegalArgumentException("Critério de ordenação inválido");
        }

        OrdenacaoStrategy ordenacaoStrategy;
        if (opcao_algoritmo.equals("quick")) {
            ordenacaoStrategy = new QuickSortStrategy(comparator);
        } else if (opcao_algoritmo.equals("insertion")) {
            ordenacaoStrategy = new InsertionSortStrategy(comparator);
        } else {
            throw new IllegalArgumentException("Algoritmo inválido");
        }

        FiltroStrategy filtroStrategy;
        switch (opcao_criterio_filtro) {
            case "todos":
                filtroStrategy = new FiltroTodos();
                break;
            case "estoque_menor_igual":
                filtroStrategy = new FiltroEstoqueMenorOuIgual(Integer.parseInt(opcao_parametro_filtro));
                break;
            case "categoria_igual":
                filtroStrategy = new FiltroCategoriaIgual(opcao_parametro_filtro);
                break;
            case "preco_intervalo":
                String[] intervalo = opcao_parametro_filtro.split("-");
                double min = Double.parseDouble(intervalo[0]);
                double max = Double.parseDouble(intervalo[1]);
                filtroStrategy = new FiltroPrecoIntervalo(min, max);
                break;
            case "descricao_contem":
                filtroStrategy = new FiltroDescricaoContem(opcao_parametro_filtro);
                break;
            default:
                throw new IllegalArgumentException("Critério de filtragem inválido");
        }

        List<Produto> produtos;
        try {
            produtos = ProdutoCSVLoader.carregaProdutosDeCSV(caminhoArquivoCSV);
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        GeradorDeRelatorios gdr = new GeradorDeRelatorios(produtos, ordenacaoStrategy, filtroStrategy);

        try {
            gdr.geraRelatorio("saida.html");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}