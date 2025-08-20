public class ProdutoFormatado extends ProdutoPadrao {
    private boolean negrito;
    private boolean italico;
    private String cor;

    public ProdutoFormatado(int id, String descricao, String categoria, int qtdEstoque, double preco, boolean negrito, boolean italico, String cor) {
        super(id, descricao, categoria, qtdEstoque, preco);
        this.negrito = negrito;
        this.italico = italico;
        this.cor = cor;
    }

    @Override
    public String formataParaImpressao() {
        String texto = super.formataParaImpressao();
        if (negrito) {
            texto = "<b>" + texto + "</b>";
        }
        if (italico) {
            texto = "<i>" + texto + "</i>";
        }
        if (cor != null && !cor.isEmpty()) {
            texto = "<span style='color:" + cor + "'>" + texto + "</span>";
        }
        return texto;
    }
}