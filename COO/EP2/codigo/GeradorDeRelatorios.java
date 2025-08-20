import java.io.PrintWriter;
import java.io.IOException;
import java.util.*;

public class GeradorDeRelatorios {
    private List<Produto> produtos;
    private OrdenacaoStrategy ordenacaoStrategy;
    private FiltroStrategy filtroStrategy;

    public GeradorDeRelatorios(List<Produto> produtos, OrdenacaoStrategy ordenacaoStrategy, FiltroStrategy filtroStrategy) {
        this.produtos = new ArrayList<>(produtos);
        this.ordenacaoStrategy = ordenacaoStrategy;
        this.filtroStrategy = filtroStrategy;
    }

    public void geraRelatorio(String arquivoSaida) throws IOException {
        ordenacaoStrategy.ordena(produtos);

        try (PrintWriter out = new PrintWriter(arquivoSaida)) {
            out.println("<!DOCTYPE html><html>");
            out.println("<head><title>Relatorio de produtos</title></head>");
            out.println("<body>");
            out.println("Relatorio de Produtos:");
            out.println("<ul>");

            int count = 0;
            for (Produto p : produtos) {
                if (filtroStrategy.filtra(p)) {
                    out.println("<li>" + p.formataParaImpressao() + "</li>");
                    count++;
                }
            }

            out.println("</ul>");
            out.println(count + " produtos listados, de um total de " + produtos.size() + ".");
            out.println("</body>");
            out.println("</html>");
        }
    }

    
}