import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ProdutoCSVLoader {
    public static List<Produto> carregaProdutosDeCSV(String caminhoArquivo) throws IOException {
        List<Produto> produtos = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(caminhoArquivo))) {
            String linha;
            boolean PrimeiraLinha = true;
            while ((linha = br.readLine()) != null) {
                if (PrimeiraLinha) {
                    PrimeiraLinha = false;
                    continue;
                }
                String[] campos = linha.split(",");
                int id = Integer.parseInt(campos[0].trim());
                String descricao = campos[1].trim();
                String categoria = campos[2].trim();
                int qtdEstoque = Integer.parseInt(campos[3].trim());
                double preco = Double.parseDouble(campos[4].trim());
                boolean negrito = Boolean.parseBoolean(campos[5].trim());
                boolean italico = Boolean.parseBoolean(campos[6].trim());
                String cor = campos[7].trim();
                produtos.add(new ProdutoFormatado(id, descricao, categoria, qtdEstoque, preco, negrito, italico, cor));
            }
        }
        return produtos;
    }
}