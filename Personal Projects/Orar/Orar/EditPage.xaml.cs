using Orar;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Xml.Schema;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace Orar
{
    [XamlCompilation(XamlCompilationOptions.Compile)]
    public partial class EditPage : ContentPage
    {
        public EditPage()
        {
            InitializeComponent();
            BindingContext = this;
        }
        protected override async void OnAppearing()
        {
            base.OnAppearing();
            CarouselEdit.ItemsSource = await App.Database.GetZile();
        }
        protected override void OnDisappearing()
        {
            base.OnDisappearing();
            CarouselEdit.ItemsSource = null;
        }
        async void SaveData(object sender, EventArgs e)
        {
            var zileOriginale = await App.Database.GetZile();
            foreach (Zi zi in CarouselEdit.ItemsSource)
            {
                await App.Database.UpdateZi(zi);
            }
            var zileUpdated = await App.Database.GetZile();

            bool updated = false;
            foreach (Zi ziOriginala in zileOriginale)
            {
                Zi ziUpdated = zileUpdated.FirstOrDefault(z => z.Id == ziOriginala.Id);
                if (VerifZile(ziOriginala, ziUpdated))
                {
                    updated = true;
                    break;
                }
            }
            if (updated)
            {
                Toast.Text = "Saved Changes";
            }
            else
            {
                Toast.Text = "No Changes Made";
            }

            await Toast.FadeTo(1, 1000);
            await Task.Delay(1000);
            await Toast.FadeTo(0, 1000);
        }
        bool VerifZile(Zi z1, Zi z2)
        {
            return z1.Activitate1 != z2.Activitate1 || z1.Activitate2 != z2.Activitate2 || z1.Activitate3 != z2.Activitate3 ||
                z1.Activitate4 != z2.Activitate4 || z1.Activitate5 != z2.Activitate5 || z1.Activitate6 != z2.Activitate6;
        }
    }
}