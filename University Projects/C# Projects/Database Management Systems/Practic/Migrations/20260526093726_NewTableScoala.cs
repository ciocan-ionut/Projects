using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Practic.Migrations
{
    /// <inheritdoc />
    public partial class NewTableScoala : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Scoli",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Nume = table.Column<string>(type: "nvarchar(100)", maxLength: 100, nullable: false),
                    Locatie = table.Column<string>(type: "nvarchar(100)", maxLength: 100, nullable: false),
                    AnInfiintare = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Scoli", x => x.Id);
                });
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Scoli");
        }
    }
}
